#pragma once

#include "IIntelliSenseInterface.h"
#include "Utilities.h"

namespace cse
{


namespace scriptEditor
{


namespace intellisense
{


using namespace DevComponents;

ref class IntelliSenseInterfaceView : public IIntelliSenseInterfaceView
{
	IIntelliSenseInterfaceModel^ BoundModel;
	IntPtr ParentViewHandle;

	utilities::AnimatedForm^ Form;
	BrightIdeasSoftware::ObjectListView^ ListView;
	BrightIdeasSoftware::OLVColumn^ ListViewDefaultColumn;
	DotNetBar::SuperTooltip^ ListViewPopup;
	DotNetBar::SuperTooltip^ InsightPopup;
	DotNetBar::StyleManagerAmbient^ ColorManager;
	utilities::SuperTooltipColorSwapper^ TooltipColorSwapper;

	property UInt32 MaximumVisibleItemCount;
	property UInt32 InsightPopupDisplayDuration;
	property UInt32 WindowWidth;
	property bool Bound
	{
		bool get() { return BoundModel != nullptr; }
	}

	void ScriptEditorPreferences_Saved(Object^ Sender, EventArgs^ E);
	void ListView_SelectionChanged(Object^ Sender, EventArgs^ E);
	void ListView_ItemActivate(Object^ Sender, EventArgs^ E);
	void ListView_KeyDown(Object^ Sender, KeyEventArgs^ E);
	void ListView_KeyUp(Object^ Sender, KeyEventArgs^ E);
	void ListView_FormatRow(Object^ Sender, BrightIdeasSoftware::FormatRowEventArgs^ E);

	static Object^ ListViewAspectGetter(Object^ RowObject);
	static Object^ ListViewImageGetter(Object^ RowObject);
	static void SuperTooltip_MarkupLinkClick(Object^ Sender, DotNetBar::MarkupLinkClickEventArgs ^ E);

	EventHandler^ ScriptEditorPreferencesSavedHandler;
	EventHandler^ ListViewSelectionChangedHandler;
	EventHandler^ ListViewItemActivateHandler;
	KeyEventHandler^ ListViewKeyDownHandler;
	KeyEventHandler^ ListViewKeyUpHandler;
	EventHandler<BrightIdeasSoftware::FormatRowEventArgs^>^ ListViewFormatRowHandler;
	utilities::AnimatedForm::TransitionCompleteHandler^ SelectFirstItemOnShowHandler;

	void ShowListViewToolTip(IntelliSenseItem^ Item);
	void HideListViewToolTip();
	void SelectFirstItemOnShow(utilities::AnimatedForm^ Sender);

	static const float kDimmedOpacity = 0.1f;
public:
	IntelliSenseInterfaceView(IntPtr ParentViewHandle);
	~IntelliSenseInterfaceView();

	virtual event EventHandler^ ItemSelected;
	virtual event EventHandler^ Dismissed;

	property bool Visible
	{
		virtual bool get()
		{
			if (Form->IsFadingIn)
				return true;
			else if (Form->IsFadingOut)
				return false;
			else
				return Form->Visible;
		}
		virtual void set(bool e) {}
	}
	property IntelliSenseItem^ Selection
	{
		virtual IntelliSenseItem^ get() { return (IntelliSenseItem^)ListView->SelectedObject; }
		virtual void set(IntelliSenseItem^ e) {}
	}

	virtual void Bind(IIntelliSenseInterfaceModel^ To);
	virtual void Unbind();

	virtual void ChangeSelection(IIntelliSenseInterfaceView::eMoveDirection Direction);
	virtual void DimOpacity();
	virtual void ResetOpacity();

	virtual void ShowInsightToolTip(IntelliSenseShowInsightToolTipArgs^ Args);
	virtual void HideInsightToolTip();

	virtual void Update();
	virtual void Show(Drawing::Point Location);
	virtual void Hide();
};


} // namespace intelliSense


} // namespace scriptEditor


} // namespace cse