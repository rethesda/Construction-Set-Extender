#include "AvalonEditTextEditor.h"
#include "Globals.h"
#include "ScriptEditorPreferences.h"

using namespace ICSharpCode::AvalonEdit::Rendering;
using namespace ICSharpCode::AvalonEdit::Document;
using namespace ICSharpCode::AvalonEdit::Editing;
using namespace System::Text::RegularExpressions;

namespace ConstructionSetExtender
{
	using namespace IntelliSense;

	namespace TextEditors
	{
		namespace AvalonEditor
		{
			ref class BracketSearchData
			{
				Char									Symbol;
				int										StartOffset;
			public:
				property int							EndOffset;
				property bool							Mismatching;

				static String^							ValidOpeningBrackets = "([{";
				static String^							ValidClosingBrackets = ")]}";

				static enum class						BracketType
				{
					e_Invalid = 0,
					e_Curved,
					e_Square,
					e_Squiggly
				};
				static enum class						BracketKind
				{
					e_Invalid = 0,
					e_Opening,
					e_Closing
				};

				BracketSearchData(Char Symbol, int StartOffset) :
					Symbol(Symbol),
					StartOffset(StartOffset)
				{
					EndOffset = -1;
					Mismatching = false;
				}

				BracketType GetType()
				{
					switch (Symbol)
					{
					case '(':
					case ')':
						return BracketType::e_Curved;
					case '[':
					case ']':
						return BracketType::e_Square;
					case '{':
					case '}':
						return BracketType::e_Squiggly;
					default:
						return BracketType::e_Invalid;
					}
				}

				BracketKind GetKind()
				{
					switch (Symbol)
					{
					case '(':
					case '[':
					case '{':
						return BracketKind::e_Opening;
					case ')':
					case ']':
					case '}':
						return BracketKind::e_Closing;
					default:
						return BracketKind::e_Invalid;
					}
				}
				int GetStartOffset() { return StartOffset; }
			};

#pragma region Interface Methods
			void AvalonEditTextEditor::SetFont(Font^ FontObject)
			{
				TextField->FontFamily = gcnew Windows::Media::FontFamily(FontObject->FontFamily->Name);
				TextField->FontSize = FontObject->Size;
				if (FontObject->Style == Drawing::FontStyle::Bold)
					TextField->FontWeight = Windows::FontWeights::Bold;
				else
					TextField->FontWeight = Windows::FontWeights::Regular;
			}

			void AvalonEditTextEditor::SetTabCharacterSize(int PixelWidth)
			{
				TextField->Options->IndentationSize = PixelWidth;
			}

			void AvalonEditTextEditor::SetContextMenu(ContextMenuStrip^% Strip)
			{
				WinFormsContainer->ContextMenuStrip = Strip;
			}

			void AvalonEditTextEditor::AddControl(Control^ ControlObject)
			{
				WinFormsContainer->Controls->Add(ControlObject);
			}

			String^ AvalonEditTextEditor::GetText(void)
			{
				return SanitizeUnicodeString(TextField->Text);
			}

			String^ AvalonEditTextEditor::GetTextAtLine( int LineNumber )
			{
				if (LineNumber > TextField->Document->LineCount || LineNumber <= 0)
					return "";
				else
					return TextField->Document->GetText(TextField->Document->GetLineByNumber(LineNumber));
			}

			UInt32 AvalonEditTextEditor::GetTextLength(void)
			{
				return TextField->Text->Length;
			}

			void AvalonEditTextEditor::SetText(String^ Text, bool PreventTextChangedEventHandling, bool ResetUndoStack)
			{
				Text = SanitizeUnicodeString(Text);

				if (PreventTextChangedEventHandling)
					SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);

				if (SetTextAnimating)
				{
					if (ResetUndoStack)
						TextField->Text = Text;
					else
					{
						SetSelectionStart(0);
						SetSelectionLength(GetTextLength());
						SetSelectedText(Text, false);
						SetSelectionLength(0);
					}

					UpdateSemanticAnalysisCache();
					UpdateCodeFoldings();
				}
				else
				{
					SetTextAnimating = true;

					TextFieldPanel->Children->Add(AnimationPrimitive);

					AnimationPrimitive->Fill =  gcnew System::Windows::Media::VisualBrush(TextField);
					AnimationPrimitive->Height = TextField->ActualHeight;
					AnimationPrimitive->Width = TextField->ActualWidth;

					TextFieldPanel->Children->Remove(TextField);

					System::Windows::Media::Animation::DoubleAnimation^ FadeOutAnimation = gcnew System::Windows::Media::Animation::DoubleAnimation(1.0,
						0.0,
						System::Windows::Duration(System::TimeSpan::FromSeconds(kSetTextFadeAnimationDuration)),
						System::Windows::Media::Animation::FillBehavior::Stop);
					SetTextPrologAnimationCache = FadeOutAnimation;

					FadeOutAnimation->Completed += SetTextAnimationCompletedHandler;
					System::Windows::Media::Animation::Storyboard^ FadeOutStoryBoard = gcnew System::Windows::Media::Animation::Storyboard();
					FadeOutStoryBoard->Children->Add(FadeOutAnimation);
					FadeOutStoryBoard->SetTargetName(FadeOutAnimation, AnimationPrimitive->Name);
					FadeOutStoryBoard->SetTargetProperty(FadeOutAnimation, gcnew System::Windows::PropertyPath(AnimationPrimitive->OpacityProperty));
					FadeOutStoryBoard->Begin(TextFieldPanel);

					if (ResetUndoStack)
						TextField->Text = Text;
					else
					{
						SetSelectionStart(0);
						SetSelectionLength(GetTextLength());
						SetSelectedText(Text, false);
						SetSelectionLength(0);
					}

					UpdateSemanticAnalysisCache();
					UpdateCodeFoldings();
				}
			}

			void AvalonEditTextEditor::InsertText( String^ Text, int Index, bool PreventTextChangedEventHandling )
			{
				if (Index > GetTextLength())
					Index = GetTextLength();

				if (PreventTextChangedEventHandling)
					SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);

				TextField->Document->Insert(Index, Text);
			}

			String^ AvalonEditTextEditor::GetSelectedText(void)
			{
				return TextField->SelectedText;
			}

			void AvalonEditTextEditor::SetSelectedText(String^ Text, bool PreventTextChangedEventHandling)
			{
				if (PreventTextChangedEventHandling)
					SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);

				TextField->SelectedText = Text;
			}

			void AvalonEditTextEditor::SetSelectionStart(int Index)
			{
				TextField->SelectionStart = Index;
			}

			void AvalonEditTextEditor::SetSelectionLength(int Length)
			{
				TextField->SelectionLength = Length;
			}

			int AvalonEditTextEditor::GetCharIndexFromPosition(Point Position)
			{
				Nullable<AvalonEdit::TextViewPosition> TextPos = TextField->TextArea->TextView->GetPosition(Windows::Point(Position.X, Position.Y));
				if (TextPos.HasValue)
					return TextField->Document->GetOffset(TextPos.Value.Line, TextPos.Value.Column);
				else
					return GetTextLength() + 1;
			}

			Point AvalonEditTextEditor::GetPositionFromCharIndex(int Index)
			{
				AvalonEdit::Document::TextLocation Location = TextField->Document->GetLocation(Index);
				Windows::Point Result = TextField->TextArea->TextView->GetVisualPosition(AvalonEdit::TextViewPosition(Location), AvalonEdit::Rendering::VisualYPosition::TextTop) - TextField->TextArea->TextView->ScrollOffset;

				return Point(Result.X, Result.Y);
			}

			Point AvalonEditTextEditor::GetAbsolutePositionFromCharIndex( int Index )
			{
				Point Result = GetPositionFromCharIndex(Index);

				for each (System::Windows::UIElement^ Itr in TextField->TextArea->LeftMargins)
					Result.X += (dynamic_cast<System::Windows::FrameworkElement^>(Itr))->ActualWidth;

				return Result;
			}

			int AvalonEditTextEditor::GetLineNumberFromCharIndex(int Index)
			{
				if (Index == -1 || TextField->Text->Length == 0)
					return 1;
				else if (Index >= TextField->Text->Length)
					Index = TextField->Text->Length - 1;

				return TextField->Document->GetLocation(Index).Line;
			}

			bool AvalonEditTextEditor::GetCharIndexInsideCommentSegment(int Index)
			{
				bool Result = true;

				if (Index >= 0 && Index < TextField->Text->Length)
				{
					AvalonEdit::Document::DocumentLine^ Line = TextField->Document->GetLineByOffset(Index);
					ScriptParser^ LocalParser = gcnew ScriptParser();
					LocalParser->Tokenize(TextField->Document->GetText(Line), false);
					if (LocalParser->GetCommentTokenIndex(LocalParser->GetTokenIndex(GetTextAtLocation(Index, false))) == -1)
						Result = false;
				}

				return Result;
			}

			int AvalonEditTextEditor::GetCurrentLineNumber(void)
			{
				return TextField->TextArea->Caret->Line;
			}

			String^ AvalonEditTextEditor::GetTokenAtCharIndex(int Offset)
			{
				return GetTextAtLocation(Offset, false)->Replace("\r\n", "")->Replace("\n", "");
			}

			String^ AvalonEditTextEditor::GetTokenAtCaretPos()
			{
				return GetTextAtLocation(GetCaretPos() - 1, false)->Replace("\r\n", "")->Replace("\n", "");
			}

			void AvalonEditTextEditor::SetTokenAtCaretPos(String^ Replacement)
			{
				GetTextAtLocation(GetCaretPos() - 1, true);
				TextField->SelectedText	= Replacement;
				SetCaretPos(TextField->SelectionStart + TextField->SelectionLength);
			}

			String^ AvalonEditTextEditor::GetTokenAtMouseLocation()
			{
				return GetTextAtLocation(LastKnownMouseClickOffset, false)->Replace("\r\n", "")->Replace("\n", "");
			}

			array<String^>^ AvalonEditTextEditor::GetTokensAtMouseLocation()
			{
				return GetTextAtLocation(LastKnownMouseClickOffset);
			}

			int AvalonEditTextEditor::GetCaretPos()
			{
				return TextField->TextArea->Caret->Offset;
			}

			void AvalonEditTextEditor::SetCaretPos(int Index)
			{
				TextField->SelectionLength = 0;
				if (Index > GetTextLength())
					Index = GetTextLength() - 1;

				if (Index > -1)
					TextField->TextArea->Caret->Offset = Index;
				else
					TextField->TextArea->Caret->Offset = 0;

				ScrollToCaret();
			}

			void AvalonEditTextEditor::ScrollToCaret()
			{
				TextField->TextArea->Caret->BringCaretToView();
			}

			IntPtr AvalonEditTextEditor::GetHandle()
			{
				return WinFormsContainer->Handle;
			}

			void AvalonEditTextEditor::FocusTextArea()
			{
				TextField->Focus();
			}

			void AvalonEditTextEditor::LoadFileFromDisk(String^ Path)
			{
				try
				{
					SetPreventTextChangedFlag(PreventTextChangeFlagState::ManualReset);
					StreamReader^ Reader = gcnew StreamReader(Path);
					String^ FileText = Reader->ReadToEnd();
					SetText(FileText, false, false);
					Reader->Close();
					SetPreventTextChangedFlag(PreventTextChangeFlagState::Disabled);
				}
				catch (Exception^ E)
				{
					DebugPrint("Error encountered when opening file for read operation!\n\tError Message: " + E->Message);
				}
			}

			void AvalonEditTextEditor::SaveScriptToDisk(String^ Path, bool PathIncludesFileName, String^% DefaultName, String^% DefaultExtension)
			{
				if (PathIncludesFileName == false)
					Path += "\\" + DefaultName + "." + DefaultExtension;

				try
				{
					TextField->Save(Path);
				}
				catch (Exception^ E)
				{
					DebugPrint("Error encountered when opening file for write operation!\n\tError Message: " + E->Message);
				}
			}

			bool AvalonEditTextEditor::GetModifiedStatus()
			{
				return ModifiedFlag;
			}

			void AvalonEditTextEditor::SetModifiedStatus(bool Modified)
			{
				ModifiedFlag = Modified;

				switch (Modified)
				{
				case true:
					ErrorColorizer->ClearLines();

					if (TextFieldInUpdateFlag == false)
						ClearFindResultIndicators();

					break;
				case false:
					break;
				}

				OnScriptModified(Modified);
			}

			bool AvalonEditTextEditor::GetInitializingStatus()
			{
				return InitializingFlag;
			}

			void AvalonEditTextEditor::SetInitializingStatus(bool Initializing)
			{
				InitializingFlag = Initializing;
			}

			int AvalonEditTextEditor::GetLastKnownMouseClickOffset()
			{
				if (LastKnownMouseClickOffset == -1)
					LastKnownMouseClickOffset = 0;

				return LastKnownMouseClickOffset;
			}

			int AvalonEditTextEditor::FindReplace(IScriptTextEditor::FindReplaceOperation Operation, String^ Query, String^ Replacement, IScriptTextEditor::FindReplaceOutput^ Output, UInt32 Options)
			{
				int Hits = 0;

				if (Operation != IScriptTextEditor::FindReplaceOperation::e_CountMatches)
				{
					ClearFindResultIndicators();
					BeginUpdate();
				}

				try
				{
					String^ Pattern = "";

					if ((Options & (UInt32)IScriptTextEditor::FindReplaceOptions::e_RegEx))
						Pattern = Query;
					else
					{
						Pattern = System::Text::RegularExpressions::Regex::Escape(Query);
						if ((Options & (UInt32)IScriptTextEditor::FindReplaceOptions::e_MatchWholeWord))
							Pattern = "\\b" + Pattern + "\\b";
					}

					System::Text::RegularExpressions::Regex^ Parser = nullptr;
					if ((Options & (UInt32)IScriptTextEditor::FindReplaceOptions::e_CaseInsensitive))
					{
						Parser = gcnew System::Text::RegularExpressions::Regex(Pattern,
										System::Text::RegularExpressions::RegexOptions::IgnoreCase|System::Text::RegularExpressions::RegexOptions::Singleline);
					}
					else
					{
						Parser = gcnew System::Text::RegularExpressions::Regex(Pattern,
										System::Text::RegularExpressions::RegexOptions::Singleline);
					}

					AvalonEdit::Editing::Selection^ TextSelection = TextField->TextArea->Selection;

					if ((Options & (UInt32)IScriptTextEditor::FindReplaceOptions::e_InSelection))
					{
						if (TextSelection->IsEmpty == false)
						{
							AvalonEdit::Document::DocumentLine ^FirstLine = nullptr, ^LastLine = nullptr;

							for each (AvalonEdit::Document::ISegment^ Itr in TextSelection->Segments)
							{
								FirstLine = TextField->TextArea->Document->GetLineByOffset(Itr->Offset);
								LastLine = TextField->TextArea->Document->GetLineByOffset(Itr->EndOffset);

								for (AvalonEdit::Document::DocumentLine^ Itr = FirstLine; Itr != LastLine->NextLine && Itr != nullptr; Itr = Itr->NextLine)
								{
									int Matches = PerformFindReplaceOperationOnSegment(Parser, Operation, Itr, Replacement, Output, Options);
									Hits += Matches;

									if (Matches == -1)
									{
										Hits = -1;
										break;
									}
								}
							}
						}
					}
					else
					{
						for each (DocumentLine^ Line in TextField->Document->Lines)
						{
							int Matches = PerformFindReplaceOperationOnSegment(Parser, Operation, Line, Replacement, Output, Options);
							Hits += Matches;

							if (Matches == -1)
							{
								Hits = -1;
								break;
							}
						}
					}
				}
				catch (Exception^ E)
				{
					Hits = -1;
					DebugPrint("Couldn't perform find/replace operation!\n\tException: " + E->Message);
				}

				if (Operation != IScriptTextEditor::FindReplaceOperation::e_CountMatches)
				{
					SetSelectionLength(0);
					RefreshBGColorizerLayer();
					EndUpdate(false);
				}

				if (Hits == -1)
				{
					MessageBox::Show("An error was encountered while performing the find/replace operation. Please recheck your search and/or replacement strings.",
									SCRIPTEDITOR_TITLE,
									MessageBoxButtons::OK,
									MessageBoxIcon::Exclamation);
				}

				return Hits;
			}

			void AvalonEditTextEditor::ToggleComment(int StartIndex)
			{
				SetPreventTextChangedFlag(PreventTextChangeFlagState::ManualReset);
				BeginUpdate();

				AvalonEdit::Editing::Selection^ TextSelection = TextField->TextArea->Selection;
				if (TextSelection->IsEmpty)
				{
					AvalonEdit::Document::DocumentLine^ Line = TextField->TextArea->Document->GetLineByOffset(StartIndex);
					if (Line != nullptr)
					{
						int FirstOffset = -1;
						for (int i = Line->Offset; i <= Line->EndOffset; i++)
						{
							char FirstChar = TextField->TextArea->Document->GetCharAt(i);
							if (AvalonEdit::Document::TextUtilities::GetCharacterClass(FirstChar) != AvalonEdit::Document::CharacterClass::Whitespace &&
								AvalonEdit::Document::TextUtilities::GetCharacterClass(FirstChar) != AvalonEdit::Document::CharacterClass::LineTerminator)
							{
								FirstOffset = i;
								break;
							}
						}

						if (FirstOffset != -1)
						{
							char FirstChar = TextField->TextArea->Document->GetCharAt(FirstOffset);
							if (FirstChar == ';')
								TextField->TextArea->Document->Replace(FirstOffset, 1, "");
							else
								TextField->TextArea->Document->Insert(FirstOffset, ";");
						}
					}
				}
				else
				{
					AvalonEdit::Document::DocumentLine ^FirstLine = nullptr, ^LastLine = nullptr;

					for each (AvalonEdit::Document::ISegment^ Itr in TextSelection->Segments)
					{
						FirstLine = TextField->TextArea->Document->GetLineByOffset(Itr->Offset);
						LastLine = TextField->TextArea->Document->GetLineByOffset(Itr->EndOffset);

						for (AvalonEdit::Document::DocumentLine^ Itr = FirstLine; Itr != LastLine->NextLine && Itr != nullptr; Itr = Itr->NextLine)
						{
							int FirstOffset = -1;
							for (int i = Itr->Offset; i < TextField->Text->Length && i <= Itr->EndOffset; i++)
							{
								char FirstChar = TextField->TextArea->Document->GetCharAt(i);
								if (AvalonEdit::Document::TextUtilities::GetCharacterClass(FirstChar) != AvalonEdit::Document::CharacterClass::Whitespace &&
									AvalonEdit::Document::TextUtilities::GetCharacterClass(FirstChar) != AvalonEdit::Document::CharacterClass::LineTerminator)
								{
									FirstOffset = i;
									break;
								}
							}

							if (FirstOffset != -1)
							{
								char FirstChar = TextField->TextArea->Document->GetCharAt(FirstOffset);

								if (FirstChar == ';')
								{
									AvalonEdit::Document::DocumentLine^ Line = TextField->TextArea->Document->GetLineByOffset(FirstOffset);
									TextField->TextArea->Document->Replace(FirstOffset, 1, "");
								}
								else
								{
									AvalonEdit::Document::DocumentLine^ Line = TextField->TextArea->Document->GetLineByOffset(FirstOffset);
									TextField->TextArea->Document->Insert(FirstOffset, ";");
								}
							}
						}
					}
				}

				EndUpdate(false);
				SetPreventTextChangedFlag(PreventTextChangeFlagState::Disabled);
			}

			void AvalonEditTextEditor::UpdateIntelliSenseLocalDatabase(void)
			{
				IntelliSenseBox->UpdateLocalVariableDatabase(SemanticAnalysisCache);

				delete TextField->SyntaxHighlighting;
				TextField->SyntaxHighlighting = CreateSyntaxHighlightDefinitions(false);
			}

			void AvalonEditTextEditor::ScrollToLine(String^ LineNumber)
			{
				int LineNo = 0;
				try { LineNo = Int32::Parse(LineNumber); } catch (...) { return; }

				GotoLine(LineNo);
			}

			void AvalonEditTextEditor::OnGotFocus(void)
			{
				FocusTextArea();

				IsFocused = true;
				SemanticAnalysisTimer->Start();
				ScrollBarSyncTimer->Start();
			}

			void AvalonEditTextEditor::HighlightScriptError(int Line)
			{
				ErrorColorizer->AddLine(Line);
				RefreshBGColorizerLayer();
			}

			void AvalonEditTextEditor::OnLostFocus( void )
			{
				IsFocused = false;
				SemanticAnalysisTimer->Stop();
				ScrollBarSyncTimer->Stop();
				IntelliSenseBox->Hide();
			}

			void AvalonEditTextEditor::ClearScriptErrorHighlights(void)
			{
				ErrorColorizer->ClearLines();
			}

			Point AvalonEditTextEditor::PointToScreen(Point Location)
			{
				return WinFormsContainer->PointToScreen(Location);
			}

			void AvalonEditTextEditor::SetEnabledState(bool State)
			{
				WPFHost->Enabled = State;
			}

			void AvalonEditTextEditor::OnPositionSizeChange(void)
			{
				IntelliSenseBox->Hide();
			}

			void AvalonEditTextEditor::BeginUpdate( void )
			{
				if (TextFieldInUpdateFlag)
					throw gcnew CSEGeneralException("Text editor is already being updated.");

				TextFieldInUpdateFlag = true;
				TextField->Document->BeginUpdate();

				SetPreventTextChangedFlag(PreventTextChangeFlagState::ManualReset);
			}

			void AvalonEditTextEditor::EndUpdate( bool FlagModification )
			{
				if (TextFieldInUpdateFlag == false)
					throw gcnew CSEGeneralException("Text editor isn't being updated.");

				TextField->Document->EndUpdate();
				TextFieldInUpdateFlag = false;

				SetPreventTextChangedFlag(PreventTextChangeFlagState::Disabled);

				if (FlagModification)
					SetModifiedStatus(true);
			}

			UInt32 AvalonEditTextEditor::GetTotalLineCount( void )
			{
				return TextField->Document->LineCount;
			}

			IntelliSense::IntelliSenseInterface^ AvalonEditTextEditor::GetIntelliSenseInterface( void )
			{
				return IntelliSenseBox;
			}

			void AvalonEditTextEditor::IndentLines( UInt32 BeginLine, UInt32 EndLine )
			{
				TextField->TextArea->IndentationStrategy->IndentLines(TextField->Document, BeginLine, EndLine);
			}

#pragma endregion

#pragma region Methods
			void AvalonEditTextEditor::Destroy()
			{
				TextField->Clear();
				MiddleMouseScrollTimer->Stop();
				ScrollBarSyncTimer->Stop();
				SemanticAnalysisTimer->Stop();
				CodeFoldingManager->Clear();
				AvalonEdit::Folding::FoldingManager::Uninstall(CodeFoldingManager);

				for each (AvalonEdit::Rendering::IBackgroundRenderer^ Itr in TextField->TextArea->TextView->BackgroundRenderers)
					delete Itr;

				TextField->TextArea->TextView->BackgroundRenderers->Clear();

				TextField->TextChanged -= TextFieldTextChangedHandler;
				TextField->TextArea->Caret->PositionChanged -= TextFieldCaretPositionChangedHandler;
				TextField->TextArea->SelectionChanged -= TextFieldSelectionChangedHandler;
				TextField->TextArea->TextCopied -= TextFieldTextCopiedHandler;
				TextField->LostFocus -= TextFieldLostFocusHandler;
				TextField->TextArea->TextView->ScrollOffsetChanged -= TextFieldScrollOffsetChangedHandler;
				TextField->PreviewKeyUp -= TextFieldKeyUpHandler;
				TextField->PreviewKeyDown -= TextFieldKeyDownHandler;
				TextField->PreviewMouseDown -= TextFieldMouseDownHandler;
				TextField->PreviewMouseUp -= TextFieldMouseUpHandler;
				TextField->PreviewMouseWheel -= TextFieldMouseWheelHandler;
				TextField->PreviewMouseHover -= TextFieldMouseHoverHandler;
				TextField->PreviewMouseHoverStopped -= TextFieldMouseHoverStoppedHandler;
				TextField->PreviewMouseMove -= TextFieldMiddleMouseScrollMoveHandler;
				TextField->PreviewMouseDown -= TextFieldMiddleMouseScrollDownHandler;
				MiddleMouseScrollTimer->Tick -= MiddleMouseScrollTimerTickHandler;
				ScrollBarSyncTimer->Tick -= ScrollBarSyncTimerTickHandler;
				ExternalVerticalScrollBar->ValueChanged -= ExternalScrollBarValueChangedHandler;
				ExternalHorizontalScrollBar->ValueChanged -= ExternalScrollBarValueChangedHandler;
				SemanticAnalysisTimer->Tick -= SemanticAnalysisTimerTickHandler;
				PREFERENCES->PreferencesSaved -= ScriptEditorPreferencesSavedHandler;

				TextFieldPanel->Children->Clear();
				WPFHost->Child = nullptr;
				WinFormsContainer->Controls->Clear();

				delete WinFormsContainer;
				delete WPFHost;
				delete TextFieldPanel;
				delete AnimationPrimitive;
				delete TextField->TextArea->TextView;
				delete TextField->TextArea;
				delete TextField;
				delete IntelliSenseBox;
				delete MiddleMouseScrollTimer;
				delete ErrorColorizer;
				delete FindReplaceColorizer;
				delete BraceColorizer;
				delete CodeFoldingManager;
				delete CodeFoldingStrategy;
				delete ScrollBarSyncTimer;
				delete SemanticAnalysisTimer;
				delete ExternalVerticalScrollBar;
				delete ExternalHorizontalScrollBar;

				IntelliSenseBox = nullptr;
				TextField->TextArea->IndentationStrategy = nullptr;
				TextField->SyntaxHighlighting = nullptr;
				TextField->Document = nullptr;
				CodeFoldingStrategy = nullptr;
				ErrorColorizer = nullptr;
				FindReplaceColorizer = nullptr;
				CodeFoldingManager = nullptr;
				BraceColorizer = nullptr;
			}

			int AvalonEditTextEditor::PerformFindReplaceOperationOnSegment(System::Text::RegularExpressions::Regex^ ExpressionParser, IScriptTextEditor::FindReplaceOperation Operation, AvalonEdit::Document::DocumentLine^ Line, String^ Replacement, IScriptTextEditor::FindReplaceOutput^ Output, UInt32 Options)
			{
				int Hits = 0, SearchStartOffset = 0;
				String^ CurrentLine = TextField->Document->GetText(Line);

				try
				{
					while (true)
					{
						System::Text::RegularExpressions::MatchCollection^ PatternMatches = ExpressionParser->Matches(CurrentLine, SearchStartOffset);

						if (PatternMatches->Count)
						{
							bool Restart = false;

							for each (System::Text::RegularExpressions::Match^ Itr in PatternMatches)
							{
								int Offset = Line->Offset + Itr->Index, Length = Itr->Length;
								Hits++;

								if (Operation == IScriptTextEditor::FindReplaceOperation::e_Replace)
								{
									TextField->Document->Replace(Offset, Length, Replacement);
									CurrentLine = TextField->Document->GetText(Line);
									FindReplaceColorizer->AddSegment(Offset, Replacement->Length);
									SearchStartOffset = Itr->Index + Replacement->Length;
									Restart = true;
									break;
								}
								else if (Operation == IScriptTextEditor::FindReplaceOperation::e_Find)
								{
									FindReplaceColorizer->AddSegment(Offset, Length);
								}
							}

							if (Restart == false)
								break;
						}
						else
							break;
					}
				}
				catch (Exception^ E)
				{
					Hits = -1;
					DebugPrint("Couldn't perform find/replace operation!\n\tException: " + E->Message);
				}

				if (Hits)
					Output(Line->LineNumber.ToString(), TextField->Document->GetText(Line));

				return Hits;
			}

			String^ AvalonEditTextEditor::GetTokenAtIndex(int Index, bool SelectText, int% StartIndexOut, int% EndIndexOut)
			{
				String^% Source = TextField->Text;
				int SearchIndex = Source->Length, SubStrStart = 0, SubStrEnd = SearchIndex;
				StartIndexOut = -1; EndIndexOut = -1;

				if (Index < SearchIndex && Index >= 0)
				{
					for (int i = Index; i > 0; i--)
					{
						if (ScriptParser::DefaultDelimiters->IndexOf(Source[i]) != -1)
						{
							SubStrStart = i + 1;
							break;
						}
					}

					for (int i = Index; i < SearchIndex; i++)
					{
						if (ScriptParser::DefaultDelimiters->IndexOf(Source[i]) != -1)
						{
							SubStrEnd = i;
							break;
						}
					}
				}
				else
					return "";

				if (SubStrStart > SubStrEnd)
					return "";
				else
				{
					if (SelectText)
					{
						TextField->SelectionStart = SubStrStart;
						TextField->SelectionLength = SubStrEnd - SubStrStart;
					}

					StartIndexOut = SubStrStart; EndIndexOut = SubStrEnd;
					return Source->Substring(SubStrStart, SubStrEnd - SubStrStart);
				}
			}

			String^ AvalonEditTextEditor::GetTextAtLocation(Point Location, bool SelectText)
			{
				int Index =	GetCharIndexFromPosition(Location), OffsetA = 0, OffsetB = 0;
				return GetTokenAtIndex(Index, SelectText, OffsetA, OffsetB);
			}

			String^ AvalonEditTextEditor::GetTextAtLocation(int Index, bool SelectText)
			{
				int OffsetA = 0, OffsetB = 0;
				return GetTokenAtIndex(Index, SelectText, OffsetA, OffsetB);
			}

			array<String^>^ AvalonEditTextEditor::GetTextAtLocation( int Index )
			{
				int OffsetA = 0, OffsetB = 0, Throwaway = 0;
				array<String^>^ Result = gcnew array<String^>(3);

				Result[1] = GetTokenAtIndex(Index, false, OffsetA, OffsetB);
				Result[0] = GetTokenAtIndex(OffsetA - 2, false, Throwaway, Throwaway);
				Result[2] = GetTokenAtIndex(OffsetB + 2, false, Throwaway, Throwaway);

				return Result;
			}

			bool AvalonEditTextEditor::GetCharIndexInsideStringSegment( int Index )
			{
				bool Result = true;

				if (Index < TextField->Text->Length)
				{
					AvalonEdit::Document::DocumentLine^ Line = TextField->Document->GetLineByOffset(Index);
					Result = ScriptParser::GetIndexInsideString(TextField->Document->GetText(Line), Index - Line->Offset);
				}

				return Result;
			}

			void AvalonEditTextEditor::GotoLine(int Line)
			{
				if (Line > 0 && Line <= TextField->LineCount)
				{
					TextField->TextArea->Caret->Line = Line;
					TextField->TextArea->Caret->Column = 0;
					ScrollToCaret();
					FocusTextArea();
				}
				else
				{
					MessageBox::Show("Invalid line number.", SCRIPTEDITOR_TITLE, MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			}

			void AvalonEditTextEditor::RefreshBGColorizerLayer()
			{
				TextField->TextArea->TextView->InvalidateLayer(ICSharpCode::AvalonEdit::Rendering::KnownLayer::Text);
			}

			void AvalonEditTextEditor::RefreshTextView()
			{
				TextField->TextArea->TextView->Redraw();
			}

			void AvalonEditTextEditor::HandleTextChangeEvent()
			{
				if (InitializingFlag)
				{
					InitializingFlag = false;
					SetModifiedStatus(false);
					ClearFindResultIndicators();
				}
				else
				{
					SetModifiedStatus(true);
					if (PreventTextChangedEventFlag == PreventTextChangeFlagState::AutoReset)
						PreventTextChangedEventFlag = PreventTextChangeFlagState::Disabled;
					else if (PreventTextChangedEventFlag == PreventTextChangeFlagState::Disabled)
					{
						if (TextField->SelectionStart - 1 >= 0 &&
							GetCharIndexInsideCommentSegment(TextField->SelectionStart - 1) == false &&
							GetCharIndexInsideStringSegment(TextField->SelectionStart - 1) == false)
						{
							if ((LastKeyThatWentDown != System::Windows::Input::Key::Back || GetTokenAtCaretPos() != "") &&
								TextField->TextArea->Selection->IsMultiline == false)
							{
								IntelliSenseBox->Show(IntelliSenseBox->LastOperation, false, false);
							}
							else
								IntelliSenseBox->Hide();
						}
					}
				}
			}

			void AvalonEditTextEditor::StartMiddleMouseScroll(System::Windows::Input::MouseButtonEventArgs^ E)
			{
				IsMiddleMouseScrolling = true;

				MiddleMouseScrollStartPoint = E->GetPosition(TextField);

				TextField->Cursor = (TextField->ExtentWidth > TextField->ViewportWidth) || (TextField->ExtentHeight > TextField->ViewportHeight) ? System::Windows::Input::Cursors::ScrollAll : System::Windows::Input::Cursors::IBeam;
				TextField->CaptureMouse();
				MiddleMouseScrollTimer->Start();
			}

			void AvalonEditTextEditor::StopMiddleMouseScroll()
			{
				TextField->Cursor = System::Windows::Input::Cursors::IBeam;
				TextField->ReleaseMouseCapture();
				MiddleMouseScrollTimer->Stop();
				IsMiddleMouseScrolling = false;
			}

			void AvalonEditTextEditor::UpdateCodeFoldings()
			{
				if (IsFocused && CodeFoldingStrategy != nullptr)
				{
#if BUILD_AVALONEDIT_VERSION == AVALONEDIT_5_0_1
					int FirstErrorOffset = 0;
					IEnumerable<AvalonEdit::Folding::NewFolding^>^ Foldings = CodeFoldingStrategy->CreateNewFoldings(TextField->Document, FirstErrorOffset);
					CodeFoldingManager->UpdateFoldings(Foldings, FirstErrorOffset);
#else
					CodeFoldingStrategy->UpdateFoldings(CodeFoldingManager, TextField->Document);
#endif
				}
			}

			void AvalonEditTextEditor::SynchronizeExternalScrollBars()
			{
				SynchronizingExternalScrollBars = true;

				int ScrollBarHeight = TextField->ExtentHeight - TextField->ViewportHeight + 155;
				int ScrollBarWidth = TextField->ExtentWidth - TextField->ViewportWidth + 155;
				int VerticalOffset = TextField->VerticalOffset;
				int HorizontalOffset = TextField->HorizontalOffset;

				if (ScrollBarHeight <= 0)
					ExternalVerticalScrollBar->Enabled = false;
				else if (!ExternalVerticalScrollBar->Enabled)
					ExternalVerticalScrollBar->Enabled = true;

				if (ScrollBarWidth <= 0)
					ExternalHorizontalScrollBar->Enabled = false;
				else if (!ExternalHorizontalScrollBar->Enabled)
					ExternalHorizontalScrollBar->Enabled = true;

				ExternalVerticalScrollBar->Maximum = ScrollBarHeight;
				ExternalVerticalScrollBar->Minimum = 0;
				if (VerticalOffset >= 0 && VerticalOffset <= ScrollBarHeight)
					ExternalVerticalScrollBar->Value = VerticalOffset;

				ExternalHorizontalScrollBar->Maximum = ScrollBarWidth;
				ExternalHorizontalScrollBar->Minimum = 0;
				if (HorizontalOffset >= 0 && HorizontalOffset <= ScrollBarHeight)
					ExternalHorizontalScrollBar->Value = HorizontalOffset;

				SynchronizingExternalScrollBars = false;
			}

			RTBitmap^ AvalonEditTextEditor::RenderFrameworkElement( System::Windows::FrameworkElement^ Element )
			{
				double TopLeft = 0;
				double TopRight = 0;
				int Width = (int)Element->ActualWidth;
				int Height = (int)Element->ActualHeight;
				double DpiX = 96; // this is the magic number
				double DpiY = 96; // this is the magic number

				System::Windows::Media::PixelFormat ReturnFormat = System::Windows::Media::PixelFormats::Default;
				System::Windows::Media::VisualBrush^ ElementBrush = gcnew System::Windows::Media::VisualBrush(Element);
				System::Windows::Media::DrawingVisual^ Visual = gcnew System::Windows::Media::DrawingVisual();

				System::Windows::Media::DrawingContext^ Context = Visual->RenderOpen();
				Context->DrawRectangle(ElementBrush, nullptr, System::Windows::Rect(TopLeft, TopRight, Width, Height));
				Context->Close();

				RTBitmap^ Bitmap = gcnew RTBitmap(Width, Height, DpiX, DpiY, ReturnFormat);
				Bitmap->Render(Visual);

				return Bitmap;
			}

			void AvalonEditTextEditor::ClearFindResultIndicators()
			{
				FindReplaceColorizer->ClearSegments();
				RefreshBGColorizerLayer();
			}

			void AvalonEditTextEditor::MoveTextSegment( AvalonEdit::Document::ISegment^ Segment, MoveSegmentDirection Direction )
			{
				int StartOffset = Segment->Offset, EndOffset = Segment->EndOffset;
				AvalonEdit::Document::DocumentLine^ PreviousLine = nullptr;
				AvalonEdit::Document::DocumentLine^ NextLine = nullptr;

				if (StartOffset - 1 >= 0)
					PreviousLine = TextField->Document->GetLineByOffset(StartOffset - 1);
				if (EndOffset + 1 < GetTextLength())
					NextLine = TextField->Document->GetLineByOffset(EndOffset + 1);

				String^ SegmentText = TextField->Document->GetText(Segment);

				switch (Direction)
				{
				case MoveSegmentDirection::Up:
					if (PreviousLine != nullptr)
					{
						String^ PreviousText = TextField->Document->GetText(PreviousLine);
						int InsertOffset = PreviousLine->Offset;

						TextField->Document->Remove(PreviousLine);
						if (Segment->EndOffset + 1 >= GetTextLength())
							TextField->Document->Remove(Segment->Offset, Segment->Length);
						else
							TextField->Document->Remove(Segment->Offset, Segment->Length + 1);

						TextField->Document->Insert(InsertOffset, SegmentText + "\n" + PreviousText);

						SetCaretPos(InsertOffset);
					}
					break;
				case MoveSegmentDirection::Down:
					if (NextLine != nullptr)
					{
						String^ NextText = TextField->Document->GetText(NextLine);
						int InsertOffset = NextLine->EndOffset - Segment->Length - NextLine->Length;
						String^ InsertText = NextText + "\n" + SegmentText;

						if (NextLine->EndOffset + 1 >= GetTextLength())
							TextField->Document->Remove(NextLine->Offset, NextLine->Length);
						else
							TextField->Document->Remove(NextLine->Offset, NextLine->Length + 1);
						TextField->Document->Remove(Segment);

						if (InsertOffset - 1 >= 0)
							InsertOffset--;

						TextField->Document->Insert(InsertOffset, InsertText);

						SetCaretPos(InsertOffset + InsertText->Length);
					}
					break;
				}
			}

			void AvalonEditTextEditor::SearchBracesForHighlighting( int CaretPos )
			{
				BraceColorizer->ClearHighlight();

				if (TextField->TextArea->Selection->IsEmpty)
				{
					DocumentLine^ CurrentLine = TextField->Document->GetLineByOffset(CaretPos);
					int OpenBraceOffset = -1, CloseBraceOffset = -1, RelativeCaretPos = -1;
					ScriptParser^ LocalParser = gcnew ScriptParser();
					Stack<BracketSearchData^>^ BracketStack = gcnew Stack<BracketSearchData^>();
					List<BracketSearchData^>^ ParsedBracketList = gcnew List<BracketSearchData^>();

					if (CurrentLine != nullptr)
					{
						RelativeCaretPos = CaretPos - CurrentLine->Offset;
						String^ Text = TextField->Document->GetText(CurrentLine);
						LocalParser->Tokenize(Text, true);
						if (LocalParser->Valid)
						{
							for (int i = 0; i < LocalParser->TokenCount; i++)
							{
								String^ Token = LocalParser->Tokens[i];
								Char Delimiter = LocalParser->Delimiters[i];
								int TokenIndex = LocalParser->Indices[i];
								int DelimiterIndex = TokenIndex + Token->Length;

								if (LocalParser->GetCommentTokenIndex(-1) == i)
									break;

								if (BracketSearchData::ValidOpeningBrackets->IndexOf(Delimiter) != -1)
								{
									BracketStack->Push(gcnew BracketSearchData(Delimiter, DelimiterIndex));
								}
								else if (BracketSearchData::ValidClosingBrackets->IndexOf(Delimiter) != -1)
								{
									if (BracketStack->Count == 0)
									{
										BracketSearchData^ DelinquentBracket = gcnew BracketSearchData(Delimiter, -1);
										DelinquentBracket->EndOffset = DelimiterIndex;
										DelinquentBracket->Mismatching = true;
										ParsedBracketList->Add(DelinquentBracket);
									}
									else
									{
										BracketSearchData^ CurrentBracket = BracketStack->Pop();
										BracketSearchData Buffer(Delimiter, DelimiterIndex);

										if (CurrentBracket->GetType() == Buffer.GetType() && CurrentBracket->GetKind() == BracketSearchData::BracketKind::e_Opening)
										{
											CurrentBracket->EndOffset = DelimiterIndex;
										}
										else
										{
											CurrentBracket->Mismatching = true;
										}

										ParsedBracketList->Add(CurrentBracket);
									}
								}
							}

							while (BracketStack->Count)
							{
								BracketSearchData^ DelinquentBracket = BracketStack->Pop();
								DelinquentBracket->EndOffset = -1;
								DelinquentBracket->Mismatching = true;
								ParsedBracketList->Add(DelinquentBracket);
							}

							if (ParsedBracketList->Count)
							{
								for each (BracketSearchData^ Itr in ParsedBracketList)
								{
									if	((Itr->GetStartOffset() <= RelativeCaretPos && Itr->EndOffset >= RelativeCaretPos) ||
										(Itr->GetStartOffset() <= RelativeCaretPos && Itr->EndOffset == -1) ||
										(Itr->GetStartOffset() == -1 && Itr->EndOffset >= RelativeCaretPos))
									{
										OpenBraceOffset = Itr->GetStartOffset();
										CloseBraceOffset = Itr->EndOffset;
										break;
									}
								}
							}
						}
					}

					if (OpenBraceOffset != -1)
						OpenBraceOffset += CurrentLine->Offset;
					if (CloseBraceOffset != -1)
						CloseBraceOffset += CurrentLine->Offset;

					BraceColorizer->SetHighlight(OpenBraceOffset, CloseBraceOffset);
				}

				TextField->TextArea->TextView->InvalidateLayer(BraceColorizer->Layer);
			}

			AvalonEditHighlightingDefinition^ AvalonEditTextEditor::CreateSyntaxHighlightDefinitions( bool UpdateStableDefs )
			{
				if (UpdateStableDefs)
					SyntaxHighlightingManager->UpdateBaseDefinitions();

				List<String^>^ LocalVars = gcnew List<String^>();
				if (SemanticAnalysisCache)
				{
					for each (ObScriptSemanticAnalysis::Variable^ Itr in SemanticAnalysisCache->Variables)
						LocalVars->Add(Itr->Name);
				}

				AvalonEditHighlightingDefinition^ Result = SyntaxHighlightingManager->GenerateHighlightingDefinition(LocalVars);
				return Result;
			}

			String^ AvalonEditTextEditor::SanitizeUnicodeString( String^ In )
			{
				String^ Result = In->Replace((wchar_t)0xA0, (wchar_t)0x20);		// replace unicode non-breaking whitespaces with ANSI equivalents

				return Result;
			}
#pragma endregion

#pragma region Events
			void AvalonEditTextEditor::OnScriptModified(bool ModificationState)
			{
				ScriptModified(this, gcnew TextEditorScriptModifiedEventArgs(ModificationState));
			}

			void AvalonEditTextEditor::OnKeyDown(System::Windows::Input::KeyEventArgs^ E)
			{
				Int32 KeyState = System::Windows::Input::KeyInterop::VirtualKeyFromKey(E->Key);

				if ((E->KeyboardDevice->Modifiers & System::Windows::Input::ModifierKeys::Control) == System::Windows::Input::ModifierKeys::Control)
					KeyState |= (int)Keys::Control;
				if ((E->KeyboardDevice->Modifiers & System::Windows::Input::ModifierKeys::Alt) == System::Windows::Input::ModifierKeys::Alt)
					KeyState |= (int)Keys::Alt;
				if ((E->KeyboardDevice->Modifiers & System::Windows::Input::ModifierKeys::Shift) == System::Windows::Input::ModifierKeys::Shift)
					KeyState |= (int)Keys::Shift;

				KeyEventArgs^ TunneledArgs = gcnew KeyEventArgs((Keys)KeyState);
				KeyDown(this, TunneledArgs);
			}

			void AvalonEditTextEditor::OnMouseClick(System::Windows::Input::MouseButtonEventArgs^ E)
			{
				MouseButtons Buttons = MouseButtons::None;
				switch (E->ChangedButton)
				{
				case System::Windows::Input::MouseButton::Left:
					Buttons = MouseButtons::Left;
					break;
				case System::Windows::Input::MouseButton::Right:
					Buttons = MouseButtons::Right;
					break;
				case System::Windows::Input::MouseButton::Middle:
					Buttons = MouseButtons::Middle;
					break;
				case System::Windows::Input::MouseButton::XButton1:
					Buttons = MouseButtons::XButton1;
					break;
				case System::Windows::Input::MouseButton::XButton2:
					Buttons = MouseButtons::XButton2;
					break;
				}

				MouseClick(this, gcnew TextEditorMouseClickEventArgs(Buttons,
																	E->ClickCount,
																	E->GetPosition(TextField).X,
																	E->GetPosition(TextField).Y,
																	LastKnownMouseClickOffset));
			}
#pragma endregion

#pragma region Event Handlers
			void AvalonEditTextEditor::TextField_TextChanged(Object^ Sender, EventArgs^ E)
			{
				HandleTextChangeEvent();
				SearchBracesForHighlighting(GetCaretPos());
			}

			void AvalonEditTextEditor::TextField_CaretPositionChanged(Object^ Sender, EventArgs^ E)
			{
				if (TextField->TextArea->Caret->Line != PreviousLineBuffer)
				{
					IntelliSenseBox->Enabled = true;
					IntelliSenseBox->LastOperation = IntelliSenseInterface::Operation::Default;
					IntelliSenseBox->OverrideThresholdCheck = false;
					PreviousLineBuffer = TextField->TextArea->Caret->Line;
					RefreshBGColorizerLayer();
				}

				if (TextField->TextArea->Selection->IsEmpty)
					SearchBracesForHighlighting(GetCaretPos());
			}

			void AvalonEditTextEditor::TextField_ScrollOffsetChanged(Object^ Sender, EventArgs^ E)
			{
				if (SynchronizingInternalScrollBars == false)
					SynchronizeExternalScrollBars();

				System::Windows::Vector CurrentOffset = TextField->TextArea->TextView->ScrollOffset;
				System::Windows::Vector Delta = CurrentOffset - PreviousScrollOffsetBuffer;
				PreviousScrollOffsetBuffer = CurrentOffset;

				IntelliSenseBox->Hide();
			}

			void AvalonEditTextEditor::TextField_TextCopied( Object^ Sender, AvalonEdit::Editing::TextEventArgs^ E )
			{
				try
				{
					Clipboard::Clear();						// to remove HTML formatting
					Clipboard::SetText(E->Text);
				}
				catch (Exception^ X)
				{
					DebugPrint("Exception raised while accessing the clipboard.\n\tException: " + X->Message, true);
				}
			}

			void AvalonEditTextEditor::TextField_KeyDown(Object^ Sender, System::Windows::Input::KeyEventArgs^ E)
			{
				LastKeyThatWentDown = E->Key;

				if (IsMiddleMouseScrolling)
				{
					StopMiddleMouseScroll();
				}

				int SelStart = TextField->SelectionStart, SelLength = TextField->SelectionLength;

				if (IntelliSenseInterface::GetTriggered(E->Key))
				{
					IntelliSenseBox->Enabled = true;

					if (TextField->SelectionStart - 1 >= 0 &&
						GetCharIndexInsideCommentSegment(TextField->SelectionStart - 1) == false &&
						GetCharIndexInsideStringSegment(TextField->SelectionStart - 1) == false)
					{
						try
						{
							switch (E->Key)
							{
							case System::Windows::Input::Key::OemPeriod:
								{
									IntelliSenseBox->Show(IntelliSenseInterface::Operation::Dot, false, true);
									SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);
									break;
								}
							case System::Windows::Input::Key::Space:
								{
									String^ Token = GetTextAtLocation(TextField->SelectionStart - 1, false)->Replace("\n", "");

									if (ScriptParser::GetScriptTokenType(Token) == ObScriptSemanticAnalysis::ScriptTokenType::Call)
									{
										IntelliSenseBox->Show(IntelliSenseInterface::Operation::Call, false, true);
										SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);
									}
									else if (ScriptParser::GetScriptTokenType(Token) == ObScriptSemanticAnalysis::ScriptTokenType::Set ||
											 ScriptParser::GetScriptTokenType(Token) == ObScriptSemanticAnalysis::ScriptTokenType::Let)
									{
										IntelliSenseBox->Show(IntelliSenseInterface::Operation::Assign, false, true);
										SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);
									}
									else
										IntelliSenseBox->LastOperation = IntelliSenseInterface::Operation::Default;

									break;
								}
							case System::Windows::Input::Key::OemTilde:
								if (E->KeyboardDevice->Modifiers == System::Windows::Input::ModifierKeys::None)
								{
									IntelliSenseBox->Show(IntelliSenseInterface::Operation::Snippet, false, true);
									SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);
								}

								break;
							default:
								{
									IntelliSenseBox->LastOperation = IntelliSenseInterface::Operation::Default;
									break;
								}
							}

							IntelliSenseBox->OverrideThresholdCheck = false;
						}
						catch (Exception^ E)
						{
							DebugPrint("IntelliSenseInterface raised an exception while initializing.\n\tException: " + E->Message, true);
						}
					}
				}

				switch (E->Key)
				{
				case System::Windows::Input::Key::Q:
					if (E->KeyboardDevice->Modifiers == System::Windows::Input::ModifierKeys::Control)
					{
						ToggleComment(TextField->SelectionStart);

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					break;
				case System::Windows::Input::Key::Enter:
					if (E->KeyboardDevice->Modifiers == System::Windows::Input::ModifierKeys::Control)
					{
						if (!IntelliSenseBox->Visible)
							IntelliSenseBox->Show(IntelliSenseInterface::Operation::Default, true, false);

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					break;
				case System::Windows::Input::Key::Escape:
					if (IntelliSenseBox->Visible)
					{
						IntelliSenseBox->Hide();
						IntelliSenseBox->Enabled = false;
						IntelliSenseBox->LastOperation = IntelliSenseInterface::Operation::Default;
						IntelliSenseBox->OverrideThresholdCheck = false;

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}

					ClearFindResultIndicators();
					break;
				case System::Windows::Input::Key::Tab:
					if (IntelliSenseBox->Visible)
					{
						SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);
						IntelliSenseBox->PickSelection();
						FocusTextArea();

						IntelliSenseBox->LastOperation = IntelliSenseInterface::Operation::Default;
						IntelliSenseBox->OverrideThresholdCheck = false;

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					break;
				case System::Windows::Input::Key::Up:
					if (IntelliSenseBox->Visible)
					{
						IntelliSenseBox->ChangeSelection(IntelliSenseInterface::MoveDirection::Up);

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					else if (E->KeyboardDevice->Modifiers == System::Windows::Input::ModifierKeys::Control)
					{
						SetPreventTextChangedFlag(PreventTextChangeFlagState::ManualReset);

						MoveTextSegment(TextField->Document->GetLineByOffset(GetCaretPos()), MoveSegmentDirection::Up);

						SetPreventTextChangedFlag(PreventTextChangeFlagState::Disabled);

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					break;
				case System::Windows::Input::Key::Down:
					if (IntelliSenseBox->Visible)
					{
						IntelliSenseBox->ChangeSelection(IntelliSenseInterface::MoveDirection::Down);

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					else if (E->KeyboardDevice->Modifiers == System::Windows::Input::ModifierKeys::Control)
					{
						SetPreventTextChangedFlag(PreventTextChangeFlagState::ManualReset);

						MoveTextSegment(TextField->Document->GetLineByOffset(GetCaretPos()), MoveSegmentDirection::Down);

						SetPreventTextChangedFlag(PreventTextChangeFlagState::Disabled);

						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					break;
				case System::Windows::Input::Key::Z:
				case System::Windows::Input::Key::Y:
					if (E->KeyboardDevice->Modifiers == System::Windows::Input::ModifierKeys::Control)
						SetPreventTextChangedFlag(PreventTextChangeFlagState::AutoReset);
					break;
				case System::Windows::Input::Key::PageUp:
				case System::Windows::Input::Key::PageDown:
					if (IntelliSenseBox->Visible || E->KeyboardDevice->Modifiers == System::Windows::Input::ModifierKeys::Control)
					{
						HandleKeyEventForKey(E->Key);
						E->Handled = true;
					}
					break;
				}

				OnKeyDown(E);
			}

			void AvalonEditTextEditor::TextField_KeyUp(Object^ Sender, System::Windows::Input::KeyEventArgs^ E)
			{
				if (E->Key == KeyToPreventHandling)
				{
					E->Handled = true;
					KeyToPreventHandling = System::Windows::Input::Key::None;
					return;
				}
			}

			void AvalonEditTextEditor::TextField_MouseDown(Object^ Sender, System::Windows::Input::MouseButtonEventArgs^ E)
			{
				Nullable<AvalonEdit::TextViewPosition> Location = TextField->GetPositionFromPoint(E->GetPosition(TextField));
				if (Location.HasValue)
				{
					LastKnownMouseClickOffset = TextField->Document->GetOffset(Location.Value.Line, Location.Value.Column);
				}
				else
				{
					SetCaretPos(GetTextLength());
				}
			}

			void AvalonEditTextEditor::TextField_MouseUp(Object^ Sender, System::Windows::Input::MouseButtonEventArgs^ E)
			{
				Nullable<AvalonEdit::TextViewPosition> Location = TextField->GetPositionFromPoint(E->GetPosition(TextField));
				if (Location.HasValue)
				{
					LastKnownMouseClickOffset = TextField->Document->GetOffset(Location.Value.Line, Location.Value.Column);

					if (E->ChangedButton == System::Windows::Input::MouseButton::Right && TextField->TextArea->Selection->IsEmpty)
						SetCaretPos(LastKnownMouseClickOffset);
				}
				else
				{
					SetCaretPos(GetTextLength());
				}

				if (IntelliSenseBox->Visible)
				{
					IntelliSenseBox->Hide();
	//				IntelliSenseBox->Enabled = false;		why disable it?
					IntelliSenseBox->LastOperation = IntelliSenseInterface::Operation::Default;
					IntelliSenseBox->OverrideThresholdCheck = false;
				}

				IntelliSenseBox->HideQuickViewToolTip();

				OnMouseClick(E);
			}

			void AvalonEditTextEditor::TextField_MouseWheel(Object^ Sender, System::Windows::Input::MouseWheelEventArgs^ E)
			{
				if (IntelliSenseBox->Visible)
				{
					if (E->Delta < 0)
						IntelliSenseBox->ChangeSelection(IntelliSenseInterface::MoveDirection::Down);
					else
						IntelliSenseBox->ChangeSelection(IntelliSenseInterface::MoveDirection::Up);

					E->Handled = true;
				}
				else
					IntelliSenseBox->HideQuickViewToolTip();
			}

			void AvalonEditTextEditor::TextField_MouseHover(Object^ Sender, System::Windows::Input::MouseEventArgs^ E)
			{
				Nullable<AvalonEdit::TextViewPosition> ViewLocation = TextField->GetPositionFromPoint(E->GetPosition(TextField));
				if (ViewLocation.HasValue)
				{
					int Offset = TextField->Document->GetOffset(ViewLocation.Value.Line, ViewLocation.Value.Column);
					Point Location = GetAbsolutePositionFromCharIndex(Offset);

					if (TextField->Text->Length > 0)
					{
						array<String^>^ Tokens = GetTextAtLocation(Offset);
						if (!GetCharIndexInsideCommentSegment(Offset))
							IntelliSenseBox->ShowQuickViewTooltip(Tokens[1], Tokens[0], Location);
					}
				}
			}

			void AvalonEditTextEditor::TextField_MouseHoverStopped(Object^ Sender, System::Windows::Input::MouseEventArgs^ E)
			{
				IntelliSenseBox->HideQuickViewToolTip();
			}

			void AvalonEditTextEditor::TextField_SelectionChanged(Object^ Sender, EventArgs^ E)
			{
				;//
			}

			void AvalonEditTextEditor::TextField_LostFocus(Object^ Sender, System::Windows::RoutedEventArgs^ E)
			{
				;//
			}

			void AvalonEditTextEditor::TextField_MiddleMouseScrollMove(Object^ Sender, System::Windows::Input::MouseEventArgs^ E)
			{
				static double SlowScrollFactor = 9;

				if (TextField->IsMouseCaptured)
				{
					System::Windows::Point CurrentPosition = E->GetPosition(TextField);

					System::Windows::Vector Delta = CurrentPosition - MiddleMouseScrollStartPoint;
					Delta.Y /= SlowScrollFactor;
					Delta.X /= SlowScrollFactor;

					MiddleMouseCurrentScrollOffset = Delta;
				}
			}

			void AvalonEditTextEditor::TextField_MiddleMouseScrollDown(Object^ Sender, System::Windows::Input::MouseButtonEventArgs^ E)
			{
				if (!IsMiddleMouseScrolling && E->ChangedButton ==  System::Windows::Input::MouseButton::Middle)
				{
					StartMiddleMouseScroll(E);
				}
				else if (IsMiddleMouseScrolling)
				{
					StopMiddleMouseScroll();
				}
			}

			void AvalonEditTextEditor::MiddleMouseScrollTimer_Tick(Object^ Sender, EventArgs^ E)
			{
				static double AccelerateScrollFactor = 0.0;

				if (IsMiddleMouseScrolling)
				{
					TextField->ScrollToVerticalOffset(TextField->VerticalOffset + MiddleMouseCurrentScrollOffset.Y);
					TextField->ScrollToHorizontalOffset(TextField->HorizontalOffset + MiddleMouseCurrentScrollOffset.X);

					MiddleMouseCurrentScrollOffset += MiddleMouseCurrentScrollOffset * AccelerateScrollFactor;
				}
			}

			void AvalonEditTextEditor::ScrollBarSyncTimer_Tick( Object^ Sender, EventArgs^ E )
			{
				SynchronizingInternalScrollBars = false;
				SynchronizeExternalScrollBars();
			}

			void AvalonEditTextEditor::SemanticAnalysisTimer_Tick( Object^ Sender, EventArgs^ E )
			{
				UpdateSemanticAnalysisCache();
				UpdateIntelliSenseLocalDatabase();
				UpdateCodeFoldings();
			}

			void AvalonEditTextEditor::ExternalScrollBar_ValueChanged( Object^ Sender, EventArgs^ E )
			{
				if (SynchronizingExternalScrollBars == false)
				{
					SynchronizingInternalScrollBars = true;

					int VerticalOffset = ExternalVerticalScrollBar->Value;
					int HorizontalOffset = ExternalHorizontalScrollBar->Value;

					VScrollBar^ VertSender = dynamic_cast<VScrollBar^>(Sender);
					HScrollBar^ HortSender = dynamic_cast<HScrollBar^>(Sender);

					if (VertSender != nullptr)
					{
						TextField->ScrollToVerticalOffset(VerticalOffset);
					}
					else if (HortSender != nullptr)
					{
						TextField->ScrollToHorizontalOffset(HorizontalOffset);
					}
				}
			}

			void AvalonEditTextEditor::SetTextAnimation_Completed( Object^ Sender, EventArgs^ E )
			{
				SetTextPrologAnimationCache->Completed -= SetTextAnimationCompletedHandler;
				SetTextPrologAnimationCache = nullptr;

				TextFieldPanel->Children->Remove(AnimationPrimitive);
				TextFieldPanel->Children->Add(TextField);

				System::Windows::Media::Animation::DoubleAnimation^ FadeInAnimation = gcnew System::Windows::Media::Animation::DoubleAnimation(0.0,
					1.0,
					System::Windows::Duration(System::TimeSpan::FromSeconds(kSetTextFadeAnimationDuration)),
					System::Windows::Media::Animation::FillBehavior::Stop);
				System::Windows::Media::Animation::Storyboard^ FadeInStoryBoard = gcnew System::Windows::Media::Animation::Storyboard();
				FadeInStoryBoard->Children->Add(FadeInAnimation);
				FadeInStoryBoard->SetTargetName(FadeInAnimation, TextField->Name);
				FadeInStoryBoard->SetTargetProperty(FadeInAnimation, gcnew System::Windows::PropertyPath(TextField->OpacityProperty));
				FadeInStoryBoard->Begin(TextFieldPanel);

				SetTextAnimating = false;
			}

			void AvalonEditTextEditor::ScriptEditorPreferences_Saved( Object^ Sender, EventArgs^ E )
			{
				if (TextField->SyntaxHighlighting != nullptr)
				{
					delete TextField->SyntaxHighlighting;
					TextField->SyntaxHighlighting = nullptr;
				}
				if (CodeFoldingStrategy != nullptr)
				{
					delete CodeFoldingStrategy;
					CodeFoldingStrategy = nullptr;
				}
				if (TextField->TextArea->IndentationStrategy != nullptr)
				{
					delete TextField->TextArea->IndentationStrategy;
					TextField->TextArea->IndentationStrategy = nullptr;
				}

				TextField->SyntaxHighlighting = CreateSyntaxHighlightDefinitions(true);

				if (PREFERENCES->FetchSettingAsInt("CodeFolding", "Appearance"))
					CodeFoldingStrategy = gcnew AvalonEditObScriptCodeFoldingStrategy(this);

				TextField->Options->CutCopyWholeLine = PREFERENCES->FetchSettingAsInt("CutCopyEntireLine", "General");
				TextField->Options->ShowSpaces = PREFERENCES->FetchSettingAsInt("ShowSpaces", "Appearance");
				TextField->Options->ShowTabs = PREFERENCES->FetchSettingAsInt("ShowTabs", "Appearance");
				TextField->WordWrap = PREFERENCES->FetchSettingAsInt("WordWrap", "Appearance");

				if (PREFERENCES->FetchSettingAsInt("AutoIndent", "General"))
					TextField->TextArea->IndentationStrategy = gcnew AvalonEditObScriptIndentStrategy(this, true, true);
				else
					TextField->TextArea->IndentationStrategy = gcnew AvalonEdit::Indentation::DefaultIndentationStrategy();

				Color ForegroundColor = PREFERENCES->LookupColorByKey("ForegroundColor");
				Color BackgroundColor = PREFERENCES->LookupColorByKey("BackgroundColor");

				WPFHost->ForeColor = ForegroundColor;
				WPFHost->BackColor = BackgroundColor;
				WinFormsContainer->ForeColor = ForegroundColor;
				WinFormsContainer->BackColor = BackgroundColor;

				System::Windows::Media::SolidColorBrush^ ForegroundBrush = gcnew System::Windows::Media::SolidColorBrush(Windows::Media::Color::FromArgb(255,
																													ForegroundColor.R,
																													ForegroundColor.G,
																													ForegroundColor.B));
				System::Windows::Media::SolidColorBrush^ BackgroundBrush = gcnew System::Windows::Media::SolidColorBrush(Windows::Media::Color::FromArgb(255,
																													BackgroundColor.R,
																													BackgroundColor.G,
																													BackgroundColor.B));

				TextField->Foreground = ForegroundBrush;
				TextField->Background = BackgroundBrush;
				TextField->LineNumbersForeground = ForegroundBrush;
				TextFieldPanel->Background = BackgroundBrush;

				RefreshTextView();
			}
#pragma endregion

			AvalonEditTextEditor::AvalonEditTextEditor(Font^ Font, UInt32 ParentWorkspaceIndex)
			{
				this->ParentWorkspaceIndex = ParentWorkspaceIndex;

				WinFormsContainer = gcnew Panel();
				WPFHost = gcnew ElementHost();
				TextFieldPanel = gcnew System::Windows::Controls::DockPanel();
				TextField = gcnew AvalonEdit::TextEditor();
				AnimationPrimitive = gcnew System::Windows::Shapes::Rectangle();
				IntelliSenseBox = gcnew IntelliSenseInterface(ParentWorkspaceIndex);
				CodeFoldingManager = AvalonEdit::Folding::FoldingManager::Install(TextField->TextArea);
				CodeFoldingStrategy = nullptr;

				if (PREFERENCES->FetchSettingAsInt("CodeFolding", "Appearance"))
					CodeFoldingStrategy = gcnew AvalonEditObScriptCodeFoldingStrategy(this);

				MiddleMouseScrollTimer = gcnew Timer();
				ExternalVerticalScrollBar = gcnew VScrollBar();
				ExternalHorizontalScrollBar = gcnew HScrollBar();
				ScrollBarSyncTimer = gcnew Timer();
				SemanticAnalysisTimer = gcnew Timer();

				TextFieldTextChangedHandler = gcnew EventHandler(this, &AvalonEditTextEditor::TextField_TextChanged);
				TextFieldCaretPositionChangedHandler = gcnew EventHandler(this, &AvalonEditTextEditor::TextField_CaretPositionChanged);
				TextFieldScrollOffsetChangedHandler = gcnew EventHandler(this, &AvalonEditTextEditor::TextField_ScrollOffsetChanged);
				TextFieldTextCopiedHandler = gcnew AvalonEditTextEventHandler(this, &AvalonEditTextEditor::TextField_TextCopied);
				TextFieldKeyUpHandler = gcnew System::Windows::Input::KeyEventHandler(this, &AvalonEditTextEditor::TextField_KeyUp);
				TextFieldKeyDownHandler = gcnew System::Windows::Input::KeyEventHandler(this, &AvalonEditTextEditor::TextField_KeyDown);
				TextFieldMouseDownHandler = gcnew System::Windows::Input::MouseButtonEventHandler(this, &AvalonEditTextEditor::TextField_MouseDown);
				TextFieldMouseUpHandler = gcnew System::Windows::Input::MouseButtonEventHandler(this, &AvalonEditTextEditor::TextField_MouseUp);
				TextFieldMouseWheelHandler = gcnew System::Windows::Input::MouseWheelEventHandler(this, &AvalonEditTextEditor::TextField_MouseWheel);
				TextFieldMouseHoverHandler = gcnew System::Windows::Input::MouseEventHandler(this, &AvalonEditTextEditor::TextField_MouseHover);
				TextFieldMouseHoverStoppedHandler = gcnew System::Windows::Input::MouseEventHandler(this, &AvalonEditTextEditor::TextField_MouseHoverStopped);
				TextFieldSelectionChangedHandler = gcnew EventHandler(this, &AvalonEditTextEditor::TextField_SelectionChanged);
				TextFieldLostFocusHandler = gcnew System::Windows::RoutedEventHandler(this, &AvalonEditTextEditor::TextField_LostFocus);
				TextFieldMiddleMouseScrollMoveHandler = gcnew System::Windows::Input::MouseEventHandler(this, &AvalonEditTextEditor::TextField_MiddleMouseScrollMove);
				TextFieldMiddleMouseScrollDownHandler = gcnew System::Windows::Input::MouseButtonEventHandler(this, &AvalonEditTextEditor::TextField_MiddleMouseScrollDown);
				MiddleMouseScrollTimerTickHandler = gcnew EventHandler(this, &AvalonEditTextEditor::MiddleMouseScrollTimer_Tick);
				ScrollBarSyncTimerTickHandler = gcnew EventHandler(this, &AvalonEditTextEditor::ScrollBarSyncTimer_Tick);
				SemanticAnalysisTimerTickHandler = gcnew EventHandler(this, &AvalonEditTextEditor::SemanticAnalysisTimer_Tick);
				ExternalScrollBarValueChangedHandler = gcnew EventHandler(this, &AvalonEditTextEditor::ExternalScrollBar_ValueChanged);
				SetTextAnimationCompletedHandler = gcnew EventHandler(this, &AvalonEditTextEditor::SetTextAnimation_Completed);
				ScriptEditorPreferencesSavedHandler = gcnew EventHandler(this, &AvalonEditTextEditor::ScriptEditorPreferences_Saved);

				System::Windows::NameScope::SetNameScope(TextFieldPanel, gcnew System::Windows::NameScope());
				TextFieldPanel->Background = gcnew Windows::Media::SolidColorBrush(Windows::Media::Color::FromArgb(255, 255, 255, 255));
				TextFieldPanel->VerticalAlignment = System::Windows::VerticalAlignment::Stretch;

				TextField->Name = "AvalonEditTextEditorInstance";
				TextField->Options->AllowScrollBelowDocument = false;
				TextField->Options->EnableEmailHyperlinks = false;
				TextField->Options->EnableHyperlinks = true;
				TextField->Options->RequireControlModifierForHyperlinkClick = true;
				TextField->Options->CutCopyWholeLine = PREFERENCES->FetchSettingAsInt("CutCopyEntireLine", "General");
				TextField->Options->ShowSpaces = PREFERENCES->FetchSettingAsInt("ShowSpaces", "Appearance");
				TextField->Options->ShowTabs = PREFERENCES->FetchSettingAsInt("ShowTabs", "Appearance");
				TextField->WordWrap = PREFERENCES->FetchSettingAsInt("WordWrap", "Appearance");
				TextField->ShowLineNumbers = true;
				TextField->HorizontalScrollBarVisibility = System::Windows::Controls::ScrollBarVisibility::Hidden;
				TextField->VerticalScrollBarVisibility = System::Windows::Controls::ScrollBarVisibility::Hidden;
				TextField->SyntaxHighlighting = CreateSyntaxHighlightDefinitions(true);

				Color ForegroundColor = PREFERENCES->LookupColorByKey("ForegroundColor");
				Color BackgroundColor = PREFERENCES->LookupColorByKey("BackgroundColor");

				WPFHost->ForeColor = ForegroundColor;
				WPFHost->BackColor = BackgroundColor;
				WinFormsContainer->ForeColor = ForegroundColor;
				WinFormsContainer->BackColor = BackgroundColor;

				System::Windows::Media::SolidColorBrush^ ForegroundBrush = gcnew System::Windows::Media::SolidColorBrush(Windows::Media::Color::FromArgb(255,
																													ForegroundColor.R,
																													ForegroundColor.G,
																													ForegroundColor.B));
				System::Windows::Media::SolidColorBrush^ BackgroundBrush = gcnew System::Windows::Media::SolidColorBrush(Windows::Media::Color::FromArgb(255,
																													BackgroundColor.R,
																													BackgroundColor.G,
																													BackgroundColor.B));

				TextField->Foreground = ForegroundBrush;
				TextField->Background = BackgroundBrush;
				TextField->LineNumbersForeground = ForegroundBrush;

				TextField->TextArea->TextView->BackgroundRenderers->Add(ErrorColorizer = gcnew AvalonEditScriptErrorBGColorizer(TextField,
																																KnownLayer::Background));
				TextField->TextArea->TextView->BackgroundRenderers->Add(FindReplaceColorizer = gcnew AvalonEditFindReplaceBGColorizer(TextField,
																																KnownLayer::Background));
				TextField->TextArea->TextView->BackgroundRenderers->Add(BraceColorizer = gcnew AvalonEditBraceHighlightingBGColorizer(TextField,
																																KnownLayer::Background));
				TextField->TextArea->TextView->BackgroundRenderers->Add(gcnew AvalonEditSelectionBGColorizer(TextField, KnownLayer::Background));
				TextField->TextArea->TextView->BackgroundRenderers->Add(gcnew AvalonEditLineLimitBGColorizer(TextField, KnownLayer::Background));
				TextField->TextArea->TextView->BackgroundRenderers->Add(gcnew AvalonEditCurrentLineBGColorizer(TextField, KnownLayer::Background));

				TextField->TextArea->IndentationStrategy = nullptr;
				if (PREFERENCES->FetchSettingAsInt("AutoIndent", "General"))
					TextField->TextArea->IndentationStrategy = gcnew AvalonEditObScriptIndentStrategy(this, true, true);
				else
					TextField->TextArea->IndentationStrategy = gcnew AvalonEdit::Indentation::DefaultIndentationStrategy();

				AnimationPrimitive->Name = "AnimationPrimitive";

				TextFieldPanel->RegisterName(AnimationPrimitive->Name, AnimationPrimitive);
				TextFieldPanel->RegisterName(TextField->Name, TextField);
				TextFieldPanel->Background = BackgroundBrush;

				TextFieldPanel->Children->Add(TextField);

				InitializingFlag = false;
				ModifiedFlag = false;
				PreventTextChangedEventFlag = PreventTextChangeFlagState::Disabled;
				KeyToPreventHandling = System::Windows::Input::Key::None;
				LastKeyThatWentDown = System::Windows::Input::Key::None;
				IsMiddleMouseScrolling = false;

				MiddleMouseScrollTimer->Interval = 16;

				IsFocused = true;

				LastKnownMouseClickOffset = 0;

				ScrollBarSyncTimer->Interval = 200;
				ScrollBarSyncTimer->Start();

				ExternalVerticalScrollBar->Dock = DockStyle::Right;
				ExternalVerticalScrollBar->SmallChange = 30;
				ExternalVerticalScrollBar->LargeChange = 155;

				ExternalHorizontalScrollBar->Dock = DockStyle::Bottom;
				ExternalHorizontalScrollBar->SmallChange = 30;
				ExternalHorizontalScrollBar->LargeChange = 155;

				SynchronizingInternalScrollBars = false;
				SynchronizingExternalScrollBars = false;
				PreviousScrollOffsetBuffer = System::Windows::Vector(0.0, 0.0);

				SetTextAnimating = false;
				SetTextPrologAnimationCache = nullptr;

				SemanticAnalysisTimer->Interval = 5000;
				SemanticAnalysisTimer->Start();

				TextFieldInUpdateFlag = false;
				PreviousLineBuffer = -1;
				SemanticAnalysisCache = gcnew ObScriptSemanticAnalysis::AnalysisData();

				WinFormsContainer->Dock = DockStyle::Fill;
				WinFormsContainer->BorderStyle = BorderStyle::FixedSingle;
				WinFormsContainer->Controls->Add(WPFHost);
				WinFormsContainer->Controls->Add(ExternalVerticalScrollBar);
				WinFormsContainer->Controls->Add(ExternalHorizontalScrollBar);

				WPFHost->Dock = DockStyle::Fill;
				WPFHost->Child = TextFieldPanel;

				SetFont(Font);

				TextField->TextChanged += TextFieldTextChangedHandler;
				TextField->TextArea->Caret->PositionChanged += TextFieldCaretPositionChangedHandler;
				TextField->TextArea->SelectionChanged += TextFieldSelectionChangedHandler;
				TextField->TextArea->TextCopied += TextFieldTextCopiedHandler;
				TextField->LostFocus += TextFieldLostFocusHandler;
				TextField->TextArea->TextView->ScrollOffsetChanged += TextFieldScrollOffsetChangedHandler;
				TextField->PreviewKeyUp += TextFieldKeyUpHandler;
				TextField->PreviewKeyDown += TextFieldKeyDownHandler;
				TextField->PreviewMouseDown += TextFieldMouseDownHandler;
				TextField->PreviewMouseUp += TextFieldMouseUpHandler;
				TextField->PreviewMouseWheel += TextFieldMouseWheelHandler;
				TextField->PreviewMouseHover += TextFieldMouseHoverHandler;
				TextField->PreviewMouseHoverStopped += TextFieldMouseHoverStoppedHandler;
				TextField->PreviewMouseMove += TextFieldMiddleMouseScrollMoveHandler;
				TextField->PreviewMouseDown += TextFieldMiddleMouseScrollDownHandler;
				MiddleMouseScrollTimer->Tick += MiddleMouseScrollTimerTickHandler;
				ScrollBarSyncTimer->Tick += ScrollBarSyncTimerTickHandler;
				ExternalVerticalScrollBar->ValueChanged += ExternalScrollBarValueChangedHandler;
				ExternalHorizontalScrollBar->ValueChanged += ExternalScrollBarValueChangedHandler;
				SemanticAnalysisTimer->Tick += SemanticAnalysisTimerTickHandler;
				PREFERENCES->PreferencesSaved += ScriptEditorPreferencesSavedHandler;
			}

			AvalonEditTextEditor::~AvalonEditTextEditor()
			{
				AvalonEditTextEditor::Destroy();
			}

			Control^ AvalonEditTextEditor::GetContainer()
			{
				return WinFormsContainer;
			}

			ObScriptSemanticAnalysis::AnalysisData^ AvalonEditTextEditor::GetSemanticAnalysisCache(void)
			{
				return SemanticAnalysisCache;
			}

			void AvalonEditTextEditor::UpdateSemanticAnalysisCache()
			{
				SemanticAnalysisCache->PerformAnalysis(GetText(), ObScriptSemanticAnalysis::ScriptType::None,
													   ObScriptSemanticAnalysis::AnalysisData::Operation::FillVariables |
													   ObScriptSemanticAnalysis::AnalysisData::Operation::FillControlBlocks,
													   nullptr);
			}
		}
	}
}