#include"MainFrame.h"
#include"run.h"
#include"instruction_set.h"

wxString ToWxString(const std::string& str)
{
	return  wxString(str.c_str(), wxConvUTF8);
}

std::string ToString(const wxString& str)
{
	return str.ToStdString();
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_OPEN, MainFrame::OnOpen)
EVT_MENU(wxID_SAVE, MainFrame::OnSave)
EVT_MENU(wxID_SAVEAS, MainFrame::OnSaveAs)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(wxID_EXECUTE, MainFrame::OnRun)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_MENU(wxID_HELP, MainFrame::OnHelp)
EVT_MENU(ON_LOAD, MainFrame::OnLoadProgram)
EVT_BUTTON(ButtonID::ON_SET_MEM, MainFrame::OnSetMemory)
EVT_BUTTON(ButtonID::ON_VIEW_MEM, MainFrame::OnViewMemory)
EVT_BUTTON(ButtonID::DEBUG_BUTTON, MainFrame::OnDebug)
EVT_BUTTON(ButtonID::EXECUTE_BUTTON, MainFrame::OnExecute)
EVT_BUTTON(ButtonID::STOP_DB_BUTTON, MainFrame::OnStopDebug)
END_EVENT_TABLE()

MainFrame::MainFrame() :wxFrame(nullptr, wxID_ANY, "8086 Simulator", wxPoint(30, 30), wxSize(800, 800))
{
	//StatusBar
	this->CreateStatusBar();

	//MenuBar
	MenuBar = new wxMenuBar();

	FileMenu = new wxMenu();
	FileMenu->Append(wxID_OPEN, _("Open\tCtrl+O"));
	FileMenu->Append(wxID_SAVE, _("Save\tCtrl+S"));
	FileMenu->Append(wxID_SAVEAS, _("Save As\tCtrl+Shift+S"));
	FileMenu->AppendSeparator();
	FileMenu->Append(wxID_EXIT, _("Exit"));

	HelpMenu = new wxMenu();
	HelpMenu->Append(wxID_HELP, _("Help"));
	HelpMenu->Append(wxID_ABOUT, _("About"));


	MenuBar->Append(FileMenu, _("&File"));
	MenuBar->Append(HelpMenu, _("&More"));

	this->SetMenuBar(MenuBar);

	//ToolBar
	ToolBar = this->CreateToolBar();
	ToolBar->AddTool(wxID_OPEN, _("Open"), wxArtProvider::GetBitmap("wxART_FILE_OPEN", wxART_OTHER, wxSize(16, 16)), _("Open"));
	ToolBar->AddTool(wxID_SAVE, _("Save"), wxArtProvider::GetBitmap("wxART_FLOPPY", wxART_OTHER, wxSize(16, 16)), _("Save"));
	ToolBar->AddTool(ON_LOAD, _("Load"), wxArtProvider::GetBitmap("wxART_FILE_SAVE", wxART_OTHER, wxSize(16, 16)), _("Load Program"));
	ToolBar->AddTool(wxID_EXECUTE, _("Execute"), wxArtProvider::GetBitmap("wxART_GO_FORWARD", wxART_OTHER, wxSize(16, 16)), _("Load + Run"));
	ToolBar->Realize();


	//EditBox
	TextBoxPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	TextBoxStaticBox = new wxStaticBox(TextBoxPanel, wxID_ANY, "");
	TextBoxStaticBoxSizer = new wxStaticBoxSizer(TextBoxStaticBox, wxHORIZONTAL);
	Editor = new wxStyledTextCtrl(TextBoxStaticBox, wxID_ANY, wxPoint(0, 20), wxSize(200, 800));
	Editor->SetMarginType(1, wxSTC_MARGIN_NUMBER);
	Editor->SetMarginWidth(1, 80);
	Editor->SetLexer(wxSTC_LEX_ASM);
	Editor->StyleSetForeground(wxSTC_H_TAGUNKNOWN, wxColour(0, 150, 0));
	Editor->SetUseHorizontalScrollBar(false);
	Editor->SetUseVerticalScrollBar(true);
	TextBoxStaticBoxSizer->Add(Editor, wxEXPAND);
	TextBoxPanel->SetSizer(TextBoxStaticBoxSizer);

	//SEGMENT INITIALIZER
	SegmentInitializerPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	SI_PanelStaticBox = new wxStaticBox(SegmentInitializerPanel, wxID_ANY, PANEL::SEGMENT_INITIALIZER);
	SI_PanelStaticBoxSizer = new wxStaticBoxSizer(SI_PanelStaticBox, wxVERTICAL);

	CS_Text_Label = new wxStaticText(SI_PanelStaticBox, wxID_ANY, REGISTER::CS + ":", wxPoint(5, 23));
	CS_TextCtrl = new wxTextCtrl(SI_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 20), wxSize(50, 20));
	CS_TextCtrl->SetMaxLength(4);
	CS_SET_Button = new wxButton(SI_PanelStaticBox, ButtonID::ON_SET_CS, BUTTON::SET, wxPoint(100, 20), wxSize(60, 22));

	SS_Text_Label = new wxStaticText(SI_PanelStaticBox, wxID_ANY, REGISTER::SS + ":", wxPoint(5, 48));
	SS_TextCtrl = new wxTextCtrl(SI_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 45), wxSize(50, 20));
	SS_TextCtrl->SetMaxLength(4);
	SS_SET_Button = new wxButton(SI_PanelStaticBox, ButtonID::ON_SET_SS, BUTTON::SET, wxPoint(100, 45), wxSize(60, 22));

	DS_Text_Label = new wxStaticText(SI_PanelStaticBox, wxID_ANY, REGISTER::DS + ":", wxPoint(5, 73));
	DS_TextCtrl = new wxTextCtrl(SI_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 70), wxSize(50, 20));
	DS_TextCtrl->SetMaxLength(4);
	DS_SET_Button = new wxButton(SI_PanelStaticBox, ButtonID::ON_SET_DS, BUTTON::SET, wxPoint(100, 70), wxSize(60, 22));

	ES_Text_Label = new wxStaticText(SI_PanelStaticBox, wxID_ANY, REGISTER::ES + ":", wxPoint(5, 98));
	ES_TextCtrl = new wxTextCtrl(SI_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 95), wxSize(50, 20));
	ES_TextCtrl->SetMaxLength(4);
	ES_SET_Button = new wxButton(SI_PanelStaticBox, ButtonID::ON_SET_ES, BUTTON::SET, wxPoint(100, 95), wxSize(60, 22));

	/*DS_Text_Label = new wxStaticText(SI_PanelStaticBox, wxID_ANY, REGISTER::CS + ":", wxPoint(5, 23));
	DS_TextCtrl = new wxTextCtrl(SI_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 20), wxSize(50, 20));
	DS_TextCtrl->SetMaxLength(4);
	DS_SET_Button = new wxButton(SI_PanelStaticBox, ButtonID::ON_SET_CS, BUTTON::SET, wxPoint(100, 20), wxSize(60, 22));

	ES_Text_Label = new wxStaticText(SI_PanelStaticBox, wxID_ANY, REGISTER::CS + ":", wxPoint(5, 23));
	ES_TextCtrl = new wxTextCtrl(SI_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 20), wxSize(50, 20));
	ES_TextCtrl->SetMaxLength(4);
	ES_SET_Button = new wxButton(SI_PanelStaticBox, ButtonID::ON_SET_CS, BUTTON::SET, wxPoint(100, 20), wxSize(60, 22));*/
	SegmentInitializerPanel->SetSizer(SI_PanelStaticBoxSizer);


	//FlagPanel
	FlagPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	FlagPanelStaticBox = new wxStaticBox(FlagPanel, wxID_ANY, PANEL::FLAG_REGISTER);
	FlagPanelStaticBoxSizer = new wxStaticBoxSizer(FlagPanelStaticBox, wxVERTICAL);
	FlagRegCheckList = new wxCheckListBox(FlagPanelStaticBox, wxID_ANY, wxPoint(0, 0), wxDefaultSize, wxArrayString(6, FlagRegisterArray), 1, wxDefaultValidator);
	FlagPanelStaticBoxSizer->Add(FlagRegCheckList);
	FlagPanel->SetSizer(FlagPanelStaticBoxSizer);

	//Register Panel
	RegisterPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	R_PanelStaticBox = new wxStaticBox(RegisterPanel, wxID_ANY, PANEL::REGISTER);
	R_PanelStaticBoxSizer = new wxStaticBoxSizer(R_PanelStaticBox, wxVERTICAL);
	
	H = new wxStaticText(R_PanelStaticBox, wxID_ANY, "H", wxPoint(37, 15), wxSize(20, 20));
	L = new wxStaticText(R_PanelStaticBox, wxID_ANY, "L", wxPoint(67, 15), wxSize(20, 20));
	for (int i = 0; i < 4; ++i)
	{
		std::string LABEL = std::string(GeneralPurposeRegisterArray[i * 2]).substr(0, 1) + "X:";
		GeneralPurposeRegisterLabel[GeneralPurposeRegisterArray[i]] = new wxStaticText(R_PanelStaticBox, wxID_ANY, LABEL, wxPoint(10, 33 + i * 25), wxSize(20, 20));
		RegisterTextCtrl[GeneralPurposeRegisterArray[i * 2]] = new wxTextCtrl(R_PanelStaticBox, wxID_ANY, "00", wxPoint(30, 30 + i * 25), wxSize(25, 20), wxTE_READONLY);
		RegisterTextCtrl[GeneralPurposeRegisterArray[i * 2 + 1]] = new wxTextCtrl(R_PanelStaticBox, wxID_ANY, "00", wxPoint(60, 30 + i * 25), wxSize(25, 20), wxTE_READONLY);
	}

	for (int i = 0; i < 8; ++i)
	{
		std::string LABEL = std::string(OtherRegisterArray[i]) + ":";
		OtherRegisterLabel[OtherRegisterArray[i]] = new wxStaticText(R_PanelStaticBox, wxID_ANY, LABEL, wxPoint(10, 133 + i * 25), wxSize(20, 20));
		RegisterTextCtrl[OtherRegisterArray[i]] = new wxTextCtrl(R_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 130 + i * 25), wxSize(50, 20), wxTE_READONLY);
	}

	//Instruction Pointer
	OtherRegisterLabel[REGISTER::IP] = new wxStaticText(R_PanelStaticBox, wxID_ANY, REGISTER::IP + ":", wxPoint(10, 333), wxSize(20, 20));
	RegisterTextCtrl[REGISTER::IP] = new wxTextCtrl(R_PanelStaticBox, wxID_ANY, "0000", wxPoint(30, 330), wxSize(50, 20), wxTE_READONLY);
	RegisterPanel->SetSizer(R_PanelStaticBoxSizer);

	//Memory Init Panel
	MemoryInitPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	MI_PanelStaticBox = new wxStaticBox(MemoryInitPanel, wxID_ANY, PANEL::MEMORY_INITIALIZER);
	MI_PanelStaticBoxSizer = new wxStaticBoxSizer(MI_PanelStaticBox, wxVERTICAL);
	MI_SegmentAddressLabel = new wxStaticText(MI_PanelStaticBox, wxID_ANY, "Segment Address(Hex) :", wxPoint(5, 33));
	MI_SegmentAddressTextCtrl = new wxTextCtrl(MI_PanelStaticBox, wxID_ANY, "0000", wxPoint(150, 30), wxSize(50, 20));
	MI_SegmentAddressTextCtrl->SetMaxLength(4);

	MI_OffsetAddressLabel = new wxStaticText(MI_PanelStaticBox, wxID_ANY, "Offset Address(Hex) :", wxPoint(5, 63));
	MI_OffsetAddressTextCtrl = new wxTextCtrl(MI_PanelStaticBox, wxID_ANY, "0000", wxPoint(150, 60), wxSize(50, 20));
	MI_OffsetAddressTextCtrl->SetMaxLength(4);

	MI_DataLabel = new wxStaticText(MI_PanelStaticBox, wxID_ANY, "Data(HEX) :", wxPoint(210, 63));
	MI_DataTextCtrl = new wxTextCtrl(MI_PanelStaticBox, wxID_ANY, "0000", wxPoint(280, 60), wxSize(50, 20));
	MI_DataTextCtrl->SetMaxLength(4);
	MI_SET_BUTTON = new wxButton(MI_PanelStaticBox, ButtonID::ON_SET_MEM, BUTTON::SET, wxPoint(340, 60), wxSize(50, 22));
	MemoryInitPanel->SetSizer(MI_PanelStaticBoxSizer);

	//Memory View Panel
	MemoryViewPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	MV_PanelStaticBox = new wxStaticBox(MemoryViewPanel, wxID_ANY, PANEL::MEMORY_VIEWER);
	MV_PanelStaticBoxSizer = new wxStaticBoxSizer(MV_PanelStaticBox, wxVERTICAL);

	MV_SegmentAddressLabel = new wxStaticText(MV_PanelStaticBox, wxID_ANY, "Segment Address(Hex) :", wxPoint(5, 33));
	MV_SegmentAddressTextCtrl = new wxTextCtrl(MV_PanelStaticBox, wxID_ANY, "0000", wxPoint(150, 30), wxSize(50, 20));
	MV_SegmentAddressTextCtrl->SetMaxLength(4);

	MV_OffsetAddressLabel = new wxStaticText(MV_PanelStaticBox, wxID_ANY, "Offset Address(Hex) :", wxPoint(5, 63));
	MV_OffsetAddressTextCtrl = new wxTextCtrl(MV_PanelStaticBox, wxID_ANY, "0000", wxPoint(150, 60), wxSize(50, 20));
	MV_OffsetAddressTextCtrl->SetMaxLength(4);

	MV_CountLabel = new wxStaticText(MV_PanelStaticBox, wxID_ANY, "Count(DEC) :", wxPoint(210, 63));
	MV_CountTextCtrl = new wxTextCtrl(MV_PanelStaticBox, wxID_ANY, "000", wxPoint(280, 60), wxSize(30, 20));
	MV_CountTextCtrl->SetMaxLength(3);

	MV_ViewButton = new wxButton(MV_PanelStaticBox, ButtonID::ON_VIEW_MEM, BUTTON::VIEW, wxPoint(320, 60));

	m_MemoryViewList = new wxListView(MV_PanelStaticBox, wxID_ANY, wxPoint(5, 90), wxSize(240, 315));
	m_MemoryViewList->AppendColumn("Segment");
	m_MemoryViewList->AppendColumn("Offset");
	m_MemoryViewList->AppendColumn("Data");
	MemoryViewPanel->SetSizer(MV_PanelStaticBoxSizer);

	//Debug Panel
	DebugPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	DB_StaticBox = new wxStaticBox(DebugPanel, wxID_ANY, PANEL::DEBUGGER);
	DB_StaticBoxSizer = new wxStaticBoxSizer(DB_StaticBox, wxVERTICAL);
	DB_CurrentLineLabel = new wxStaticText(DB_StaticBox, wxID_ANY, "Current Line Number : ", wxPoint(30, 35));
	DB_CurrentLineTextCtrl = new wxTextCtrl(DB_StaticBox, wxID_ANY, "---", wxPoint(150, 30), wxSize(20, 20), wxTE_READONLY);
	DB_ExecuteButton = new wxButton(DB_StaticBox, ButtonID::EXECUTE_BUTTON, BUTTON::EXECUTE, wxPoint(65, 55));
	DB_DebugButton = new wxButton(DB_StaticBox, ButtonID::DEBUG_BUTTON, BUTTON::DEBUG, wxPoint(25, 100));
	DB_StopButton = new wxButton(DB_StaticBox, ButtonID::STOP_DB_BUTTON, BUTTON::STOP, wxPoint(105, 100));
	DB_ExecuteButton->Disable();
	DB_StopButton->Disable();
	DebugPanel->SetSizer(DB_StaticBoxSizer);


	//Sizers
	LeftPanelSizer = new wxBoxSizer(wxVERTICAL);
	LeftPanelSizer->Add(SegmentInitializerPanel, 1, wxEXPAND);
	LeftPanelSizer->Add(FlagPanel, 1, wxEXPAND);
	LeftPanelSizer->Add(RegisterPanel, 3, wxEXPAND);

	RightPanelSizer = new wxBoxSizer(wxVERTICAL);
	RightPanelSizer->Add(MemoryInitPanel, 1, wxEXPAND);
	RightPanelSizer->Add(MemoryViewPanel, 4, wxEXPAND);
	RightPanelSizer->Add(DebugPanel, 1, wxEXPAND);


	MainSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(LeftPanelSizer, 1, wxEXPAND | wxALL, 1);
	MainSizer->Add(TextBoxPanel, 2, wxEXPAND | wxTOP | wxBOTTOM, 1);
	MainSizer->Add(RightPanelSizer, 2, wxEXPAND | wxALL, 1);

	this->SetSizerAndFit(MainSizer);

	Init();
}

MainFrame::~MainFrame()
{

}

void MainFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open text file"), "", "", "TEXT files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	CurrFilePath = openFileDialog.GetPath();
	Editor->LoadFile(CurrFilePath);
	TextBoxStaticBox->SetLabel(openFileDialog.GetFilename());
}

void MainFrame::OnSave(wxCommandEvent& event)
{
	if (CurrFilePath.empty())
	{
		OnSaveAs(event);
	}
	else
	{
		Editor->SaveFile(CurrFilePath);
	}

}

void MainFrame::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save text file"), "", "", "TEXT files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	CurrFilePath = saveFileDialog.GetPath();
	Editor->SaveFile(CurrFilePath);
	TextBoxStaticBox->SetLabel(saveFileDialog.GetFilename());
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	this->Close();
}

void MainFrame::Init()
{
	ProgramLoader::LoadCallBacks();
	ProgramExecutor::LoadCallBacks();
	UpdateRegisters();
	UpdateFlagRegister();
}

void MainFrame::OnRun(wxCommandEvent& event)
{

	if (CurrFilePath.empty())
	{
		OnSaveAs(event);
		if (!CurrFilePath.empty())
		{
			Run8086(ToString(CurrFilePath));
		}
	}
	else
	{
		Editor->SaveFile(CurrFilePath);
		Run8086(ToString(CurrFilePath));
	}
}

void MainFrame::OnSetMemory(wxCommandEvent& envet)
{
	//if (m_MemoryAddressTextCtrl->IsEmpty() || m_DataTextCtrl->IsEmpty())
	//{
	//	Error::Throw(ERROR_TYPE::EMPTY_FIELD);
	//	m_MemoryAddressTextCtrl->Clear();
	//	m_DataTextCtrl->Clear();
	//	m_MemoryAddressTextCtrl->AppendText("0000");
	//	m_DataTextCtrl->AppendText("00");
	//}
	//else if (MemoryManager::SetMemory(ToString(m_MemoryAddressTextCtrl->GetValue()), ToString(m_DataTextCtrl->GetValue())))//No need to report error as SetMemory will report if any.
	//{
	//	m_MemoryAddressTextCtrl->Clear();
	//	m_DataTextCtrl->Clear();
	//	m_MemoryAddressTextCtrl->AppendText("0000");
	//	m_DataTextCtrl->AppendText("00");
	//	UpdateMemory();
	//}
}

void MainFrame::OnViewMemory(wxCommandEvent& envet)
{
	UpdateMemory();
}


void MainFrame::OnSetLoadingLocation(wxCommandEvent& envet)
{
	//if (m_ProgramLoadingPanelTextCtrl->IsEmpty())
	//{
	//	Error::Throw(ERROR_TYPE::EMPTY_FIELD);
	//	m_ProgramLoadingPanelTextCtrl->AppendText("0000");
	//}
	//else
	//{
	//	std::string address = ToString(m_ProgramLoadingPanelTextCtrl->GetValue());
	//	if (Validator::IsValidHex(address))
	//	{
	//		//No need to check for overflow as user can't put more than 4 characters in this text field.
	//		m_nLoadingLocation = Converter::HexToDec(address);
	//		Converter::ToUpperString(address);
	//		Utility::_16Bit(address);
	//		m_ProgramLoadingPanelCurrentLocationTextCtrl->Clear();
	//		m_ProgramLoadingPanelCurrentLocationTextCtrl->AppendText(address);
	//		m_ProgramLoadingPanelTextCtrl->Clear();
	//		m_ProgramLoadingPanelTextCtrl->AppendText("0000");
	//	}
	//	else
	//	{
	//		Error::Throw(ERROR_TYPE::INVALID_DATA);
	//	}
	//}
}

void MainFrame::UpdateFlagRegister()
{
	FlagRegCheckList->Check(FlagRegCheckList->FindString("AF"), Register::GetFlag(Register::FLAG::AF));
	FlagRegCheckList->Check(FlagRegCheckList->FindString("CF"), Register::GetFlag(Register::FLAG::CF));
	FlagRegCheckList->Check(FlagRegCheckList->FindString("ZF"), Register::GetFlag(Register::FLAG::ZF));
	FlagRegCheckList->Check(FlagRegCheckList->FindString("SF"), Register::GetFlag(Register::FLAG::SF));
	FlagRegCheckList->Check(FlagRegCheckList->FindString("PF"), Register::GetFlag(Register::FLAG::PF));
	FlagRegCheckList->Check(FlagRegCheckList->FindString("OF"), Register::GetFlag(Register::FLAG::OF));
}

void MainFrame::UpdateRegisters()
{
	//Update main Register
	for (const std::string& REG : GeneralPurposeRegisterArray)
	{
		RegisterTextCtrl[REG]->Clear();
		const std::string& Data = Converter::DecToHex(Register::REG8(REG)).substr(0, 2);
		RegisterTextCtrl[REG]->AppendText(ToWxString(Data));
	}

	for (const std::string& REG : OtherRegisterArray)
	{
		RegisterTextCtrl[REG]->Clear();
		const std::string& Data = Converter::DecToHex(Register::REG16(REG), HEX_SIZE::WORD).substr(0, 4);
		RegisterTextCtrl[REG]->AppendText(ToWxString(Data));
	}

	RegisterTextCtrl[REGISTER::IP]->Clear();
	const std::string& Data = Converter::DecToHex(Register::IP(), HEX_SIZE::WORD).substr(0, 4);
	RegisterTextCtrl[REGISTER::IP]->AppendText(ToWxString(Data));
}


void MainFrame::UpdateMemory()
{
	/*if (m_FromMemoryAddressTextCtrl->IsEmpty() || m_CountTextCtrl->IsEmpty())
	{
		m_FromMemoryAddressTextCtrl->Clear();
		m_CountTextCtrl->Clear();
		m_FromMemoryAddressTextCtrl->AppendText("0000");
		m_CountTextCtrl->AppendText("000");
	}

	const std::string sFrom = ToString(m_FromMemoryAddressTextCtrl->GetValue());
	const std::string sCount = ToString(m_CountTextCtrl->GetValue());
	if (Validator::IsValidHex(sFrom) && Validator::IsValidInt(sCount))
	{
		m_MemoryViewList->ClearAll();
		m_MemoryViewList->AppendColumn("Address");
		m_MemoryViewList->AppendColumn("Data");

		int nFrom = Converter::HexToDec(sFrom);
		int nCount = std::stoi(sCount);

		for (int i = 0; i < nCount && (nFrom + i) <= 0xffff; ++i)
		{
			std::string address = Converter::DecToHex(nFrom + i, 16);
			std::string data = Converter::DecToHex(MemoryManager::Memory[nFrom + i]);
			m_MemoryViewList->InsertItem(i, ToWxString(address));
			m_MemoryViewList->SetItem(i, 1, ToWxString(data));
		}
	}
	else
	{
		Error::Throw(ERROR_TYPE::INVALID_DATA);
	}*/
}

void MainFrame::Clear()
{
	//Clearing Registers(Frontend)
	for (const std::string& REG : GeneralPurposeRegisterArray)
	{
		RegisterTextCtrl[REG]->Clear();
		RegisterTextCtrl[REG]->AppendText("00");
	}

	for (const std::string& REG : OtherRegisterArray)
	{
		RegisterTextCtrl[REG]->Clear();
		RegisterTextCtrl[REG]->AppendText("0000");
	}

	RegisterTextCtrl[REGISTER::IP]->Clear();
	RegisterTextCtrl[REGISTER::IP]->AppendText("0000");

	//Clearing Flag Register(Frontend)
	FlagRegCheckList->Check(FlagRegCheckList->FindString("AF"), false);
	FlagRegCheckList->Check(FlagRegCheckList->FindString("CF"), false);
	FlagRegCheckList->Check(FlagRegCheckList->FindString("ZF"), false);
	FlagRegCheckList->Check(FlagRegCheckList->FindString("SF"), false);
	FlagRegCheckList->Check(FlagRegCheckList->FindString("PF"), false);
	FlagRegCheckList->Check(FlagRegCheckList->FindString("OF"), false);
}

void MainFrame::OnDebug(wxCommandEvent& event)
{
	/*if (CurrFilePath.empty())
	{
		OnSaveAs(event);
		if (!CurrFilePath.empty())
		{
			Debug8085(ToString(CurrFilePath));
		}
	}
	else
	{
		Editor->SaveFile(CurrFilePath);
		Debug8085(ToString(CurrFilePath));
	}*/
}

void MainFrame::Run8086(const std::string& filePath)
{
	Clear();
	//Clearing Frontend
	if (LOAD_PROGRAM(filePath))//Read & Load
	{
		if (ProgramExecutor::Execute())
		{
			UpdateFlagRegister();
			UpdateRegisters();
			UpdateMemory();
			wxMessageBox(MESSAGE::SUCCESSFUL_EXECUTION, DIALOG::SUCCESS);
		}
	}
}

void MainFrame::Debug8086(const std::string& filePath)
{
	Clear();//Clearing Front End
	//if (ProgramManager::LoadProgramInMemory(filePath, m_nLoadingLocation))//Read function int LoadProgramInMemory is responsible for clearing the backend
	//{
	//	UpdateMemory();
	//	UpdateRegisters();//Updating all register but we just need to update PC at this time
	//	m_ExecuteButton->Enable();
	//	m_DebugButton->Disable();
	//	m_StopButton->Enable();
	//	m_CurrentLineTextCtrl->Clear();
	//	m_CurrentLineTextCtrl->AppendText(ToWxString(std::to_string(ProgramManager::Program[Register::iPC].line_number)));
	//	m_EditBox->SetEditable(false);//Disabling Editor
	//	m_ToolBar->Disable();//Disabling the toolbar
	//	m_EditBox->MarkerAdd(ProgramManager::Program[Register::iPC].line_number - 1, 0);
	//	m_EditBox->MarkerSetBackground(0, *wxRED);
	//}
}

void MainFrame::OnExecute(wxCommandEvent& event)
{
	//const Instruction& instruction = ProgramManager::Program[Register::iPC];

	//if (Mnemonic::Execute[instruction.mnemonic](instruction.operands))//Successful execution of a instruction
	//{
	//	UpdateFlagRegister();
	//	UpdateRegisters();
	//	UpdateMemory();
	//	m_CurrentLineTextCtrl->Clear();
	//	m_CurrentLineTextCtrl->AppendText(ToWxString(std::to_string(ProgramManager::Program[Register::iPC].line_number)));
	//	m_EditBox->MarkerDeleteAll(0);
	//	m_EditBox->MarkerAdd(ProgramManager::Program[Register::iPC].line_number - 1, 0);
	//	m_EditBox->MarkerSetBackground(0, *wxRED);
	//}
	//else if (ProgramManager::_HLT)//HLT get executed
	//{
	//	UpdateFlagRegister();
	//	UpdateRegisters();
	//	UpdateMemory();
	//	wxMessageBox(MESSAGE::SUCCESSFUL_EXECUTION, DIALOG::SUCCESS);
	//	OnStopDebug(event);
	//}
	//else//Error
	//{
	//	UpdateFlagRegister();
	//	UpdateRegisters();
	//	UpdateMemory();
	//	OnStopDebug(event);
	//}
}


void MainFrame::OnStopDebug(wxCommandEvent& event)
{
	DB_ExecuteButton->Disable();
	DB_StopButton->Disable();
	DB_DebugButton->Enable();
	DB_CurrentLineTextCtrl->Clear();
	DB_CurrentLineTextCtrl->AppendText("---");
	ToolBar->Enable();
	Editor->SetEditable(true);
	Editor->MarkerDeleteAll(0);

}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxDialog aboutDialog(this, wxID_ANY, DIALOG::ABOUT);
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
	wxHtmlWindow* html = new wxHtmlWindow(&aboutDialog, wxID_ANY, wxDefaultPosition, wxSize(380, 160), wxHW_SCROLLBAR_NEVER);
	html->SetBorders(1);
	html->LoadPage(PATH::ABOUT_HTML_FILE);
	html->SetSize(html->GetInternalRepresentation()->GetWidth(), html->GetInternalRepresentation()->GetHeight());
	dialogSizer->Add(html, 1, wxALL, 10);
	wxButton* OKButton = new wxButton(&aboutDialog, wxID_OK, _("OK"));
	OKButton->SetDefault();
	dialogSizer->Add(OKButton, 0, wxALIGN_CENTER | wxALL, 10);
	aboutDialog.SetSizer(dialogSizer);
	dialogSizer->Fit(&aboutDialog);
	aboutDialog.ShowModal();
}

void MainFrame::OnHelp(wxCommandEvent& event)
{
	wxDialog helpDialog(this, wxID_ANY, DIALOG::HELP);
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
	wxHtmlWindow* html = new wxHtmlWindow(&helpDialog, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	html->SetBorders(1);
	html->LoadPage(PATH::HELP_HTML_FILE);
	html->SetSize(html->GetInternalRepresentation()->GetWidth(), html->GetInternalRepresentation()->GetHeight());
	dialogSizer->Add(html, 1, wxALL, 10);
	wxButton* OKButton = new wxButton(&helpDialog, wxID_OK, _("OK"));
	OKButton->SetDefault();
	dialogSizer->Add(OKButton, 0, wxALIGN_CENTER | wxALL, 10);
	helpDialog.SetSizer(dialogSizer);
	dialogSizer->Fit(&helpDialog);
	helpDialog.ShowModal();
}

void MainFrame::OnLoadProgram(wxCommandEvent& event)
{
	if (CurrFilePath.empty())
	{
		OnSaveAs(event);
		if (!CurrFilePath.empty())
		{
			LoadProgram(ToString(CurrFilePath));
		}
	}
	else
	{
		Editor->SaveFile(CurrFilePath);
		LoadProgram(ToString(CurrFilePath));
	}
}

void MainFrame::LoadProgram(const std::string& filePath)
{
	Clear();//Clearing Front End
	//if (ProgramManager::LoadProgramInMemory(filePath, m_nLoadingLocation))//Read function in LoadProgramInMemory is responsible for clearing the backend
	//{
	//	UpdateFlagRegister();
	//	UpdateRegisters();
	//	UpdateMemory();
	//	wxMessageBox(MESSAGE::SUCCESSFUL_PROGRAM_LOADING, DIALOG::SUCCESS);
	//}
	//else
	//{
	//	UpdateMemory();
	//}
}