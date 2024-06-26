#pragma once

#include "SemanticAnalysis.h"
#include "Utilities.h"

namespace cse
{


namespace scriptEditor
{


namespace intellisense
{


ref class IntelliSenseItem;
interface class IIntelliSenseInterfaceView;

ref struct IntelliSenseInputEventArgs
{
	static enum class eEvent
	{
		KeyDown,
		KeyUp,
		MouseDown,
		MouseUp
	};

	property eEvent Type;

	property KeyEventArgs^ KeyEvent;
	property MouseEventArgs^ MouseEvent;
	property bool Handled;

	IntelliSenseInputEventArgs(eEvent Type, KeyEventArgs^ Source)
	{
		this->Type = Type;
		this->KeyEvent = Source;
		this->MouseEvent = nullptr;
		this->Handled = false;
	}

	IntelliSenseInputEventArgs(eEvent Type, MouseEventArgs^ Source)
	{
		this->Type = Type;
		this->KeyEvent = nullptr;
		this->MouseEvent = Source;
		this->Handled = false;
	}
};

ref struct IntelliSenseContextChangeEventArgs
{
	static enum class eEvent
	{
		Reset,

		TextChanged,
		CaretPosChanged,
		ScrollOffsetChanged,

		SemanticAnalysisCompleted
	};

	property eEvent Type;

	property int CaretPos;
	property UInt32 CurrentLineNumber;
	property int CurrentLineStartPos;
	property bool CurrentLineInsideViewport;

	property String^ ClippedLineText;				// clipped to the caret pos
	property obScriptParsing::AnalysisData^ SemanticAnalysisData;

	property Point DisplayScreenCoords;

	IntelliSenseContextChangeEventArgs(eEvent Type)
	{
		this->Type = Type;

		CaretPos = -1;
		CurrentLineNumber = 0;
		CurrentLineStartPos = -1;
		CurrentLineInsideViewport = true;

		ClippedLineText = String::Empty;
		SemanticAnalysisData = nullptr;

		DisplayScreenCoords = Point(0, 0);
	}
};

ref struct IntelliSenseInsightHoverEventArgs
{
	static enum class eEvent
	{
		HoverStart,
		HoverStop
	};

	property eEvent Type;

	property UInt32 Line;
	property String^ HoveredToken;
	property String^ PreviousToken;		// relative to the hovered token
	property bool DotOperatorInUse;
	property bool HoveringOverComment;

	property List<String^>^ ErrorMessagesForHoveredLine;
	property Point DisplayScreenCoords;

	IntelliSenseInsightHoverEventArgs(eEvent Type)
	{
		this->Type = Type;

		Line = 0;
		HoveredToken = String::Empty;
		PreviousToken = String::Empty;
		DotOperatorInUse = false;
		HoveringOverComment = false;
		ErrorMessagesForHoveredLine = gcnew List<String^>;
		DisplayScreenCoords = Point(0, 0);
	}
};

delegate void IntelliSenseInputEventHandler(Object^ Sender, IntelliSenseInputEventArgs^ E);
delegate void IntelliSenseInsightHoverEventHandler(Object^ Sender, IntelliSenseInsightHoverEventArgs^ E);
delegate void IntelliSenseContextChangeEventHandler(Object^ Sender, IntelliSenseContextChangeEventArgs^ E);

interface class IIntelliSenseInterfaceConsumer
{
	event IntelliSenseInputEventHandler^ IntelliSenseInput;
	event IntelliSenseInsightHoverEventHandler^ IntelliSenseInsightHover;
	event IntelliSenseContextChangeEventHandler^ IntelliSenseContextChange;
};


interface class IIntelliSenseInterfaceModel
{
public:
	property List<IntelliSenseItem^>^ DataStore;

	void Bind(IIntelliSenseInterfaceView^ To);
	void Unbind();
	bool IsLocalVariable(String^ Identifier);
};

ref class IntelliSenseShowInsightToolTipArgs : public utilities::IRichTooltipContentProvider
{
	String^ TooltipHeaderText_;
	String^ TooltipBodyText_;
	Image^ TooltipBodyImage_;
	String^ TooltipFooterText_;
	Image^ TooltipFooterImage_;
	Color TooltipBgColor_;
	Color TooltipTextColor_;
public:
	virtual property String^ TooltipHeaderText
	{
		String^ get() { return TooltipHeaderText_; }
		void set(String^ set) { TooltipHeaderText_ = set; }
	}
	virtual property String^ TooltipBodyText
	{
		String^ get() { return TooltipBodyText_; }
		void set(String^ set) { TooltipBodyText_ = set; }
	}
	virtual property Image^	TooltipBodyImage
	{
		Image^ get() { return TooltipBodyImage_; }
		void set(Image^ set) { TooltipBodyImage_ = set; }
	}
	virtual property String^ TooltipFooterText
	{
		String^ get() { return TooltipFooterText_; }
		void set(String^ set) { TooltipFooterText_ = set; }
	}
	virtual property Image^	TooltipFooterImage
	{
		Image^ get() { return TooltipFooterImage_; }
		void set(Image^ set) { TooltipFooterImage_ = set; }
	}
	virtual property Color TooltipBgColor
	{
		Color get() { return TooltipBgColor_; }
		void set(Color set) { TooltipBgColor_ = set; }
	}
	virtual property Color TooltipTextColor
	{
		Color get() { return TooltipTextColor_; }
		void set(Color set) { TooltipTextColor_ = set; }
	}
	property Point DisplayScreenCoords;
	property IntPtr	ParentWindowHandle;

	IntelliSenseShowInsightToolTipArgs()
	{
		TooltipHeaderText_ = String::Empty;
		TooltipBodyText_ = String::Empty;
		TooltipFooterText_ = String::Empty;
		TooltipBodyImage_ = TooltipFooterImage_ = nullptr;
		TooltipBgColor_ = Color::Empty;
		TooltipTextColor_ = Color::Empty;

		DisplayScreenCoords = Point(0, 0);
		ParentWindowHandle = IntPtr::Zero;
	}
};
 
interface class IIntelliSenseInterfaceView
{
public:
	static enum	class eMoveDirection
	{
		Up,
		Down,
	};
	
	[Flags]
	static enum class eItemFilter
	{
		None = 0,

		ScriptCommand = 1 << 0,
		ScriptVariable = 1 << 1,
		Quest = 1 << 2,
		Script = 1 << 3,
		UserFunction = 1 << 4,
		GameSetting = 1 << 5,
		GlobalVariable = 1 << 6,
		Form = 1 << 7,
		ObjectReference = 1 << 8,
	};

	event EventHandler^ ItemSelected;
	event EventHandler^ Dismissed;
	event EventHandler^ FuzzySearchToggled;

	property bool Visible;
	property IntelliSenseItem^ Selection;

	void Bind(IIntelliSenseInterfaceModel^ To);
	void Unbind();

	void ResetFilters();
	void HandleFilterShortcutKey(Keys ShortcutKey);

	void ChangeSelection(eMoveDirection Direction);
	void DimOpacity();
	void ResetOpacity();

	void ShowInsightToolTip(IntelliSenseShowInsightToolTipArgs^ Args);
	void HideInsightToolTip();

	void Update();			// refreshes the item list
	void Show(Drawing::Point Location);
	void Hide();
};


} // namespace intelliSense


} // namespace scriptEditor


} // namespace cse