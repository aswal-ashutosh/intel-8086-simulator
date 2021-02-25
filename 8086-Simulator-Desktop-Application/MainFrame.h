#pragma once
#include<wx\wx.h>
#include<wx\artprov.h>
#include<wx/stc/stc.h>
#include<wx/listctrl.h>
#include"wx/html/htmlwin.h"
#include<map>
#include"constants.h"


class MainFrame : public wxFrame
{
private:

	//Menu Bar
	wxMenuBar* MenuBar = nullptr;
	wxMenu* FileMenu = nullptr;
	wxMenu* HelpMenu = nullptr;

	//Tool Bar
	wxToolBar* ToolBar = nullptr;


	//Text Editor
	wxPanel* TextBoxPanel = nullptr;
	wxStyledTextCtrl* Editor = nullptr;
	wxStaticBox* TextBoxStaticBox = nullptr;
	wxStaticBoxSizer* TextBoxStaticBoxSizer = nullptr;

	//File
	wxString CurrFilePath;

	//Segment Initializer Panel => SRI
	wxPanel* SegmentInitializerPanel = nullptr;
	wxStaticBox* SI_PanelStaticBox = nullptr;
	wxStaticBoxSizer* SI_PanelStaticBoxSizer = nullptr;
	wxTextCtrl* CS_TextCtrl = nullptr;
	wxTextCtrl* SS_TextCtrl = nullptr;
	wxTextCtrl* DS_TextCtrl = nullptr;
	wxTextCtrl* ES_TextCtrl = nullptr;
	wxStaticText* CS_Text_Label = nullptr;
	wxStaticText* SS_Text_Label = nullptr;
	wxStaticText* DS_Text_Label = nullptr;
	wxStaticText* ES_Text_Label = nullptr;
	wxButton* CS_SET_Button = nullptr;
	wxButton* SS_SET_Button = nullptr;
	wxButton* DS_SET_Button = nullptr;
	wxButton* ES_SET_Button = nullptr;


	//Flag Rgister Panel 
	wxPanel* FlagPanel = nullptr;
	wxStaticBox* FlagPanelStaticBox = nullptr;
	wxStaticBoxSizer* FlagPanelStaticBoxSizer = nullptr;
	wxCheckListBox* FlagRegCheckList = nullptr;



	//Main Register Panel => RP
	wxPanel* RegisterPanel = nullptr;
	wxStaticBox* R_PanelStaticBox = nullptr;
	wxStaticBoxSizer* R_PanelStaticBoxSizer = nullptr;
	std::map<std::string, wxTextCtrl*> RegisterTextCtrl;
	std::map<std::string, wxStaticText*> GeneralPurposeRegisterLabel;
	std::map<std::string, wxStaticText*> OtherRegisterLabel;
	wxStaticText* H = nullptr;
	wxStaticText* L = nullptr;
	/*wxTextCtrl* m_PSW_TextCtrl = nullptr;
	wxStaticText* m_PSW_StaticText = nullptr;*/



	//Memroy Initializer Panel => MI
	wxPanel* MemoryInitPanel = nullptr;
	wxStaticBox* MI_PanelStaticBox = nullptr;
	wxStaticBoxSizer* MI_PanelStaticBoxSizer = nullptr;
	wxButton* MI_SET_BUTTON = nullptr;
	wxStaticText* MI_SegmentAddressLabel = nullptr;
	wxTextCtrl* MI_SegmentAddressTextCtrl = nullptr;
	wxStaticText* MI_OffsetAddressLabel = nullptr;
	wxTextCtrl* MI_OffsetAddressTextCtrl = nullptr;
	wxStaticText* MI_DataLabel = nullptr;
	wxTextCtrl* MI_DataTextCtrl = nullptr;



	//Memroy Viewer Panel => MV
	wxPanel* MemoryViewPanel = nullptr;
	wxStaticBox* MV_PanelStaticBox = nullptr;
	wxStaticBoxSizer* MV_PanelStaticBoxSizer = nullptr;
	wxButton* MV_ViewButton = nullptr;
	wxStaticText* MV_SegmentAddressLabel = nullptr;
	wxTextCtrl* MV_SegmentAddressTextCtrl = nullptr;
	wxStaticText* MV_OffsetAddressLabel = nullptr;
	wxTextCtrl* MV_OffsetAddressTextCtrl = nullptr;
	wxTextCtrl* MV_CountTextCtrl = nullptr;
	wxStaticText* MV_CountLabel = nullptr;
	wxListView* m_MemoryViewList = nullptr;

	//Debug Panel
	wxPanel* DebugPanel = nullptr;
	wxStaticText* DB_CurrentLineLabel = nullptr;
	wxTextCtrl* DB_CurrentLineTextCtrl = nullptr;
	wxButton* DB_ExecuteButton = nullptr;
	wxButton* DB_DebugButton = nullptr;
	wxButton* DB_StopButton = nullptr;
	wxStaticBox* DB_StaticBox = nullptr;
	wxStaticBoxSizer* DB_StaticBoxSizer = nullptr;


	//Sizers
	wxBoxSizer* MainSizer = nullptr;
	wxBoxSizer* LeftPanelSizer = nullptr;
	wxBoxSizer* RightPanelSizer = nullptr;

	//Other
	const std::string GeneralPurposeRegisterArray[8] =
	{
		REGISTER::AH, REGISTER::AL,
		REGISTER::BH, REGISTER::BL,
		REGISTER::CH, REGISTER::CL,
		REGISTER::DH, REGISTER::DL,
	};

	const std::string OtherRegisterArray[8] = 
	{ 
		REGISTER::SP, REGISTER::BP,
		REGISTER::SI, REGISTER::DI, 
		REGISTER::CS, REGISTER::SS, 
		REGISTER::DS, REGISTER::ES,
	};

	const char* FlagRegisterArray[6] = { "CF", "ZF", "SF", "OF", "PF", "AF"};

	//State
	bool m_bDebugMode = false;
	int m_nLoadingLocation = 0;//Current Program Loading Location
public:



	MainFrame();
	~MainFrame();

	//FileHandling
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

	//ProgramExecutor
	void OnRun(wxCommandEvent& envet);
	void OnDebug(wxCommandEvent& event);
	void OnExecute(wxCommandEvent& event);
	void OnStopDebug(wxCommandEvent& event);
	void Run8086(const std::string& filePath);
	void Debug8086(const std::string& filePath);

	void OnSetMemory(wxCommandEvent& envet);
	void OnSetLoadingLocation(wxCommandEvent& envet);
	void OnLoadProgram(wxCommandEvent& event);
	void LoadProgram(const std::string&);
	void OnViewMemory(wxCommandEvent& envet);
	void UpdateFlagRegister();
	void UpdateRegisters();
	void UpdateMemory();
	
	
	void OnAbout(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
	void Clear();//Will be called before running the program(Memory will not be affected)
	
	void Init();
	DECLARE_EVENT_TABLE();
};

enum ButtonID
{
	ON_SET_CS,
	ON_SET_DS,
	ON_SET_SS,
	ON_SET_ES,
	ON_SET_MEM,
	ON_VIEW_MEM,
	EXECUTE_BUTTON,
	DEBUG_BUTTON,
	STOP_DB_BUTTON,
	ON_LOAD,
};
