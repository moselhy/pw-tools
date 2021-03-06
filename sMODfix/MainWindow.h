#pragma once

#include "TranslatorService.h"
#include "LoadingScreen.h"
#include "DependencyViewer.h"
#include "..\COMMON\ecm.h"
#include "..\COMMON\gfx.h"
#include "..\COMMON\sgc.h"
#include "..\COMMON\bmd.h"
#include "..\COMMON\smd.h"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;

public ref class MainWindow : public System::Windows::Forms::Form
{
	public:
	MainWindow(void)
	{
		InitializeComponent();
		Initialize();
		mouseMoveCheck = gcnew Point(0,0);
	}

	protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~MainWindow()
	{
		if (components)
		{
			delete components;
		}
	}

	TranslatorService::SoapService^ soap;
	String^ appID;
	String^ from;
	String^ to;

	ArrayList^ fileToolTips;
	private: Point^ mouseMoveCheck;

	Options^ downgradeOptions;
	static int ecm_v136 = 32;
	static int ecm_vMAX = 67;
	static int smd_v136 = 8;
	static int smd_vMAX = 8;
	static int bon_v136 = 6;
	static int bon_vMAX = 6;
	static int ski_v136 = 9;
	static int ski_vMAX = 9;
	static int stck_v136 = 1;
	static int stck_vMAX = 1;
	static int gfx_v136 = 58;
	static int gfx_vMAX = 103;
	static int att_v136 = 0;
	static int att_vMAX = 13;
	static int sgc_v136 = 4;
	static int sgc_vMAX = 5;
	static int bmd_v136 = 5; // the refers to version of objects inside the file, not the file version itself
	static int bmd_vMAX = 6; // the refers to version of objects inside the file, not the file version itself

	private: System::Windows::Forms::Button^  button_browseIn;
	private: System::Windows::Forms::ListBox^  listBox_files;
	private: System::Windows::Forms::TextBox^  textBox_translation;
	private: System::Windows::Forms::TextBox^  textBox_directoryIn;
	private: System::Windows::Forms::ComboBox^  comboBox_filter;
	private: System::Windows::Forms::ComboBox^  comboBox_language;
	private: System::Windows::Forms::ComboBox^  comboBox_version;
	private: System::Windows::Forms::Button^  button_fix;
	private: System::Windows::Forms::Button^  button_dev;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  textBox_directoryOut;
	private: System::Windows::Forms::Button^  button_browseOut;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  textBox_Analyze;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::CheckBox^  checkBox_Translator;
	private: System::Windows::Forms::ComboBox^  comboBox_Analyze;
	private: System::Windows::Forms::CheckBox^  checkBox_gfxConvert210;
	private: System::Windows::Forms::CheckBox^  checkBox_gfxChonvert152;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel_FileCount;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar;
	private: System::Windows::Forms::CheckBox^  checkBox_ecmHook;
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->components = (gcnew System::ComponentModel::Container());
		this->button_browseIn = (gcnew System::Windows::Forms::Button());
		this->listBox_files = (gcnew System::Windows::Forms::ListBox());
		this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
		this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->textBox_translation = (gcnew System::Windows::Forms::TextBox());
		this->textBox_directoryIn = (gcnew System::Windows::Forms::TextBox());
		this->comboBox_filter = (gcnew System::Windows::Forms::ComboBox());
		this->comboBox_language = (gcnew System::Windows::Forms::ComboBox());
		this->comboBox_version = (gcnew System::Windows::Forms::ComboBox());
		this->button_fix = (gcnew System::Windows::Forms::Button());
		this->button_dev = (gcnew System::Windows::Forms::Button());
		this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
		this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
		this->comboBox_Analyze = (gcnew System::Windows::Forms::ComboBox());
		this->checkBox_Translator = (gcnew System::Windows::Forms::CheckBox());
		this->textBox_Analyze = (gcnew System::Windows::Forms::TextBox());
		this->textBox_directoryOut = (gcnew System::Windows::Forms::TextBox());
		this->button_browseOut = (gcnew System::Windows::Forms::Button());
		this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
		this->checkBox_ecmHook = (gcnew System::Windows::Forms::CheckBox());
		this->checkBox_gfxChonvert152 = (gcnew System::Windows::Forms::CheckBox());
		this->checkBox_gfxConvert210 = (gcnew System::Windows::Forms::CheckBox());
		this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
		this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
		this->toolStripProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
		this->toolStripStatusLabel_FileCount = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->contextMenuStrip1->SuspendLayout();
		this->groupBox1->SuspendLayout();
		this->groupBox2->SuspendLayout();
		this->groupBox3->SuspendLayout();
		this->statusStrip1->SuspendLayout();
		this->SuspendLayout();
		// 
		// button_browseIn
		// 
		this->button_browseIn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->button_browseIn->Location = System::Drawing::Point(411, 18);
		this->button_browseIn->Name = L"button_browseIn";
		this->button_browseIn->Size = System::Drawing::Size(75, 21);
		this->button_browseIn->TabIndex = 0;
		this->button_browseIn->Text = L"Browse...";
		this->toolTip1->SetToolTip(this->button_browseIn, L"You should select the element folder as root directory.\r\nThis root directory shou" 
			L"ld contain the gfx.pck.files and models.pck.files subdirectories.");
		this->button_browseIn->UseVisualStyleBackColor = true;
		this->button_browseIn->Click += gcnew System::EventHandler(this, &MainWindow::click_browse);
		// 
		// listBox_files
		// 
		this->listBox_files->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
			| System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->listBox_files->ContextMenuStrip = this->contextMenuStrip1;
		this->listBox_files->FormattingEnabled = true;
		this->listBox_files->Location = System::Drawing::Point(6, 19);
		this->listBox_files->Name = L"listBox_files";
		this->listBox_files->Size = System::Drawing::Size(618, 199);
		this->listBox_files->TabIndex = 0;
		this->listBox_files->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::select_file);
		this->listBox_files->DoubleClick += gcnew System::EventHandler(this, &MainWindow::doubleClick_file);
		this->listBox_files->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainWindow::mouseMove_toolTip);
		// 
		// contextMenuStrip1
		// 
		this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->copyToolStripMenuItem});
		this->contextMenuStrip1->Name = L"contextMenuStrip1";
		this->contextMenuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
		this->contextMenuStrip1->ShowImageMargin = false;
		this->contextMenuStrip1->Size = System::Drawing::Size(181, 26);
		// 
		// copyToolStripMenuItem
		// 
		this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
		this->copyToolStripMenuItem->Size = System::Drawing::Size(180, 22);
		this->copyToolStripMenuItem->Text = L"Copy Relative Path (d_gfx)";
		this->copyToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::click_Copy);
		// 
		// textBox_translation
		// 
		this->textBox_translation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->textBox_translation->Location = System::Drawing::Point(121, 234);
		this->textBox_translation->Name = L"textBox_translation";
		this->textBox_translation->Size = System::Drawing::Size(422, 20);
		this->textBox_translation->TabIndex = 2;
		// 
		// textBox_directoryIn
		// 
		this->textBox_directoryIn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->textBox_directoryIn->Enabled = false;
		this->textBox_directoryIn->Location = System::Drawing::Point(6, 19);
		this->textBox_directoryIn->Name = L"textBox_directoryIn";
		this->textBox_directoryIn->Size = System::Drawing::Size(399, 20);
		this->textBox_directoryIn->TabIndex = 1;
		// 
		// comboBox_filter
		// 
		this->comboBox_filter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->comboBox_filter->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->comboBox_filter->FormattingEnabled = true;
		this->comboBox_filter->Items->AddRange(gcnew cli::array< System::Object^  >(9) {L"*.ecm", L"*.gfx", L"*.sgc", L"*.bmd", L"*.smd", 
			L"*.bon", L"*.ski", L"*.stck", L"*.att"});
		this->comboBox_filter->Location = System::Drawing::Point(492, 19);
		this->comboBox_filter->Name = L"comboBox_filter";
		this->comboBox_filter->Size = System::Drawing::Size(63, 21);
		this->comboBox_filter->TabIndex = 2;
		this->comboBox_filter->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::click_loadFileList);
		// 
		// comboBox_language
		// 
		this->comboBox_language->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
		this->comboBox_language->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->comboBox_language->Enabled = false;
		this->comboBox_language->FormattingEnabled = true;
		this->comboBox_language->Location = System::Drawing::Point(549, 233);
		this->comboBox_language->Name = L"comboBox_language";
		this->comboBox_language->Size = System::Drawing::Size(75, 21);
		this->comboBox_language->TabIndex = 1;
		this->comboBox_language->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::change_language);
		// 
		// comboBox_version
		// 
		this->comboBox_version->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->comboBox_version->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->comboBox_version->FormattingEnabled = true;
		this->comboBox_version->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"all", L">1.3.6", L"<=1.3.6", L"unsupported"});
		this->comboBox_version->Location = System::Drawing::Point(561, 19);
		this->comboBox_version->Name = L"comboBox_version";
		this->comboBox_version->Size = System::Drawing::Size(63, 21);
		this->comboBox_version->TabIndex = 3;
		this->comboBox_version->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::click_loadFileList);
		// 
		// button_fix
		// 
		this->button_fix->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->button_fix->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
			static_cast<System::Byte>(0)));
		this->button_fix->Location = System::Drawing::Point(549, 88);
		this->button_fix->Name = L"button_fix";
		this->button_fix->Size = System::Drawing::Size(75, 21);
		this->button_fix->TabIndex = 4;
		this->button_fix->Text = L"Fix Files";
		this->button_fix->UseVisualStyleBackColor = true;
		this->button_fix->Click += gcnew System::EventHandler(this, &MainWindow::click_fix);
		// 
		// button_dev
		// 
		this->button_dev->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
		this->button_dev->Location = System::Drawing::Point(549, 260);
		this->button_dev->Name = L"button_dev";
		this->button_dev->Size = System::Drawing::Size(75, 21);
		this->button_dev->TabIndex = 5;
		this->button_dev->Text = L"Analyze";
		this->button_dev->UseVisualStyleBackColor = true;
		this->button_dev->Click += gcnew System::EventHandler(this, &MainWindow::click_analyze);
		// 
		// groupBox1
		// 
		this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->groupBox1->Controls->Add(this->textBox_directoryIn);
		this->groupBox1->Controls->Add(this->comboBox_version);
		this->groupBox1->Controls->Add(this->comboBox_filter);
		this->groupBox1->Controls->Add(this->button_browseIn);
		this->groupBox1->Location = System::Drawing::Point(1, 3);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(630, 46);
		this->groupBox1->TabIndex = 0;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"INPUT DIRECTORY";
		// 
		// groupBox2
		// 
		this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
			| System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->groupBox2->Controls->Add(this->comboBox_Analyze);
		this->groupBox2->Controls->Add(this->checkBox_Translator);
		this->groupBox2->Controls->Add(this->textBox_Analyze);
		this->groupBox2->Controls->Add(this->listBox_files);
		this->groupBox2->Controls->Add(this->button_dev);
		this->groupBox2->Controls->Add(this->comboBox_language);
		this->groupBox2->Controls->Add(this->textBox_translation);
		this->groupBox2->Location = System::Drawing::Point(1, 55);
		this->groupBox2->Name = L"groupBox2";
		this->groupBox2->Size = System::Drawing::Size(630, 287);
		this->groupBox2->TabIndex = 1;
		this->groupBox2->TabStop = false;
		this->groupBox2->Text = L"FILE LIST";
		// 
		// comboBox_Analyze
		// 
		this->comboBox_Analyze->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
		this->comboBox_Analyze->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->comboBox_Analyze->FormattingEnabled = true;
		this->comboBox_Analyze->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Verify Version", L"Filter Search Pattern", 
			L"ECM Dependencies", L"Dump GFX Structure", L"Dump ECM Structure"});
		this->comboBox_Analyze->Location = System::Drawing::Point(6, 260);
		this->comboBox_Analyze->Name = L"comboBox_Analyze";
		this->comboBox_Analyze->Size = System::Drawing::Size(109, 21);
		this->comboBox_Analyze->TabIndex = 8;
		this->comboBox_Analyze->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::change_AnalyzeType);
		// 
		// checkBox_Translator
		// 
		this->checkBox_Translator->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
		this->checkBox_Translator->AutoSize = true;
		this->checkBox_Translator->Location = System::Drawing::Point(6, 236);
		this->checkBox_Translator->Name = L"checkBox_Translator";
		this->checkBox_Translator->Size = System::Drawing::Size(109, 17);
		this->checkBox_Translator->TabIndex = 3;
		this->checkBox_Translator->Text = L"Enable Translator";
		this->checkBox_Translator->UseVisualStyleBackColor = true;
		this->checkBox_Translator->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::check_Translator);
		// 
		// textBox_Analyze
		// 
		this->textBox_Analyze->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->textBox_Analyze->Location = System::Drawing::Point(121, 260);
		this->textBox_Analyze->Name = L"textBox_Analyze";
		this->textBox_Analyze->Size = System::Drawing::Size(422, 20);
		this->textBox_Analyze->TabIndex = 6;
		this->textBox_Analyze->Text = L"SEARCH PATTERN";
		// 
		// textBox_directoryOut
		// 
		this->textBox_directoryOut->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->textBox_directoryOut->Enabled = false;
		this->textBox_directoryOut->Location = System::Drawing::Point(6, 88);
		this->textBox_directoryOut->Name = L"textBox_directoryOut";
		this->textBox_directoryOut->Size = System::Drawing::Size(456, 20);
		this->textBox_directoryOut->TabIndex = 1;
		this->textBox_directoryOut->Text = L"CHOOSE DIRECTORY";
		// 
		// button_browseOut
		// 
		this->button_browseOut->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->button_browseOut->Location = System::Drawing::Point(468, 88);
		this->button_browseOut->Name = L"button_browseOut";
		this->button_browseOut->Size = System::Drawing::Size(75, 21);
		this->button_browseOut->TabIndex = 0;
		this->button_browseOut->Text = L"Browse...";
		this->button_browseOut->UseVisualStyleBackColor = true;
		this->button_browseOut->Click += gcnew System::EventHandler(this, &MainWindow::click_browse);
		// 
		// groupBox3
		// 
		this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->groupBox3->Controls->Add(this->checkBox_ecmHook);
		this->groupBox3->Controls->Add(this->checkBox_gfxChonvert152);
		this->groupBox3->Controls->Add(this->checkBox_gfxConvert210);
		this->groupBox3->Controls->Add(this->textBox_directoryOut);
		this->groupBox3->Controls->Add(this->button_browseOut);
		this->groupBox3->Controls->Add(this->button_fix);
		this->groupBox3->Location = System::Drawing::Point(1, 348);
		this->groupBox3->Name = L"groupBox3";
		this->groupBox3->Size = System::Drawing::Size(630, 120);
		this->groupBox3->TabIndex = 2;
		this->groupBox3->TabStop = false;
		this->groupBox3->Text = L"OUTPUT SETTINGS";
		// 
		// checkBox_ecmHook
		// 
		this->checkBox_ecmHook->AutoSize = true;
		this->checkBox_ecmHook->Checked = true;
		this->checkBox_ecmHook->CheckState = System::Windows::Forms::CheckState::Checked;
		this->checkBox_ecmHook->Location = System::Drawing::Point(6, 65);
		this->checkBox_ecmHook->Name = L"checkBox_ecmHook";
		this->checkBox_ecmHook->Size = System::Drawing::Size(177, 17);
		this->checkBox_ecmHook->TabIndex = 13;
		this->checkBox_ecmHook->Text = L"ECM: Change Soulsphere Hook";
		this->checkBox_ecmHook->UseVisualStyleBackColor = true;
		this->checkBox_ecmHook->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::change_Options);
		// 
		// checkBox_gfxChonvert152
		// 
		this->checkBox_gfxChonvert152->AutoSize = true;
		this->checkBox_gfxChonvert152->Checked = true;
		this->checkBox_gfxChonvert152->CheckState = System::Windows::Forms::CheckState::Checked;
		this->checkBox_gfxChonvert152->Location = System::Drawing::Point(6, 19);
		this->checkBox_gfxChonvert152->Name = L"checkBox_gfxChonvert152";
		this->checkBox_gfxChonvert152->Size = System::Drawing::Size(174, 17);
		this->checkBox_gfxChonvert152->TabIndex = 12;
		this->checkBox_gfxChonvert152->Text = L"GFX: Convert Block 152 -> 150";
		this->checkBox_gfxChonvert152->UseVisualStyleBackColor = true;
		this->checkBox_gfxChonvert152->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::change_Options);
		// 
		// checkBox_gfxConvert210
		// 
		this->checkBox_gfxConvert210->AutoSize = true;
		this->checkBox_gfxConvert210->Checked = true;
		this->checkBox_gfxConvert210->CheckState = System::Windows::Forms::CheckState::Checked;
		this->checkBox_gfxConvert210->Location = System::Drawing::Point(6, 42);
		this->checkBox_gfxConvert210->Name = L"checkBox_gfxConvert210";
		this->checkBox_gfxConvert210->Size = System::Drawing::Size(174, 17);
		this->checkBox_gfxConvert210->TabIndex = 11;
		this->checkBox_gfxConvert210->Text = L"GFX: Convert Block 210 -> 160";
		this->checkBox_gfxConvert210->UseVisualStyleBackColor = true;
		this->checkBox_gfxConvert210->CheckedChanged += gcnew System::EventHandler(this, &MainWindow::change_Options);
		// 
		// toolTip1
		// 
		this->toolTip1->AutoPopDelay = 30000;
		this->toolTip1->InitialDelay = 500;
		this->toolTip1->ReshowDelay = 100;
		// 
		// statusStrip1
		// 
		this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripProgressBar, 
			this->toolStripStatusLabel_FileCount});
		this->statusStrip1->Location = System::Drawing::Point(0, 471);
		this->statusStrip1->Name = L"statusStrip1";
		this->statusStrip1->Size = System::Drawing::Size(632, 22);
		this->statusStrip1->TabIndex = 9;
		this->statusStrip1->Text = L"statusStrip1";
		// 
		// toolStripProgressBar
		// 
		this->toolStripProgressBar->Name = L"toolStripProgressBar";
		this->toolStripProgressBar->Size = System::Drawing::Size(480, 16);
		this->toolStripProgressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
		// 
		// toolStripStatusLabel_FileCount
		// 
		this->toolStripStatusLabel_FileCount->AutoSize = false;
		this->toolStripStatusLabel_FileCount->Name = L"toolStripStatusLabel_FileCount";
		this->toolStripStatusLabel_FileCount->Size = System::Drawing::Size(135, 17);
		this->toolStripStatusLabel_FileCount->Spring = true;
		this->toolStripStatusLabel_FileCount->Text = L"Number of Files: 0";
		this->toolStripStatusLabel_FileCount->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
		// 
		// MainWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(632, 493);
		this->Controls->Add(this->groupBox2);
		this->Controls->Add(this->groupBox1);
		this->Controls->Add(this->groupBox3);
		this->Controls->Add(this->statusStrip1);
		this->MinimumSize = System::Drawing::Size(640, 520);
		this->Name = L"MainWindow";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L" sMODfix";
		this->contextMenuStrip1->ResumeLayout(false);
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->groupBox2->ResumeLayout(false);
		this->groupBox2->PerformLayout();
		this->groupBox3->ResumeLayout(false);
		this->groupBox3->PerformLayout();
		this->statusStrip1->ResumeLayout(false);
		this->statusStrip1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

	void Initialize()
	{
		downgradeOptions = gcnew Options();
		change_Options(nullptr, nullptr);

		comboBox_filter->SelectedIndex = 0;
		comboBox_version->SelectedIndex = 1;
		comboBox_Analyze->SelectedIndex = 0;

		this->Icon = (Drawing::Icon^)((gcnew Resources::ResourceManager("sTools.icons", Reflection::Assembly::GetExecutingAssembly()))->GetObject("app"));
		this->toolTip1->SetToolTip(this->checkBox_gfxChonvert152, L"GFX 152 blocks are new and will not work in 1.3.6 client.\nEnable this option to convert them to GFX 150 blocks.\n\nRecommendation: Checked");
		this->toolTip1->SetToolTip(this->checkBox_gfxConvert210, L"GFX 210 blocks are new and will not work in 1.3.6 client.\nEnable this option to convert them to GFX 160 blocks.\n\nLimitations:\n● culling not supported (backfaces as frontfaces)\n● gfx z-order not supported (WriteZ: 1 - alpha problem)\n● texture motion not supported (TexSpeed)\n● texture animation not supported (tiled textures as video)\n\nRecommendation: Checked");
		this->toolTip1->SetToolTip(this->checkBox_ecmHook, L"ECM soulspheres uses a new hook and will not work in 1.3.6 client.\nEnable this option to use the CC_weapon hook for soulspheres.\nThe sphere EventTypes will also be translated by an xyz offset to appear close to the right hand.\n\nX-Offset: " + downgradeOptions->ecmSoulsphereHookTX.ToString("F3") + "\nY-Offset: " + downgradeOptions->ecmSoulsphereHookTY.ToString("F3") + "\nZ-Offset: " + downgradeOptions->ecmSoulsphereHookTZ.ToString("F3") + "\n\nThis option will also select one of the unsupported combine acts and copy the EventTypes\nto the coGfx blocks to enable the base gfx effects for this weapon.\n\nRecommendation: Checked");
		this->toolTip1->SetToolTip(this->button_fix, L"Fixes all files in the file list.\r\nDowngraded files will be stored in the selected output directory.");
		this->toolTip1->SetToolTip(this->comboBox_filter, L"Filter files depending on their type.");
		this->toolTip1->SetToolTip(this->comboBox_version, L"Filter files depending on their version.");
		this->toolTip1->SetToolTip(this->button_dev, L"Start analysis.\r\nDump files will be created in the selected output directory.");
		this->toolTip1->SetToolTip(this->checkBox_Translator, L"Eneable/Disable the translation service\r\n*Translation service is for available the selected items in the file list.");
		this->toolTip1->SetToolTip(this->comboBox_Analyze, L"Select a task to perform.");
	}

	void listFilesRecursive(String^ BasePath, String^ Filter, int MinVersion, int MaxVersion)
	{
		Application::DoEvents();

		String^ line;
		StreamReader^ sr;
		FileStream^ fr;
		BinaryReader^ br;
		int version = int::MinValue;
		array<String^>^ files = Directory::GetFiles(BasePath, Filter);
		for(int i=0; i<files->Length; i++)
		{
			if(Filter == "*.bmd")
			{
				BMD^ structure = gcnew BMD();
				structure->Load(files[i]);
				for(int i=0; i<structure->Objects->Length; i++)
				{
					version = Math::Max(version, (int)structure->Objects[i]->Ident->Type);
				}
			}
			if(Filter == "*.smd" || Filter == "*.bon" || Filter == "*.ski" || Filter == "*.stck")
			{
				fr = File::OpenRead(files[i]);
				br = gcnew BinaryReader(fr);
				br->BaseStream->Position = 8;
				version = br->ReadInt32();
				br->Close();
				fr->Close();
			}
			if(Filter == "*.ecm" || Filter == "*.gfx" || Filter == "*.att" || Filter == "*.sgc")
			{
				sr = gcnew StreamReader(files[i]);
				line = sr->ReadLine();
				if(line->Split(gcnew array<wchar_t>{' '})->Length>1)
				{
					version = Convert::ToInt32(line->Split(gcnew array<wchar_t>{' '})[1]);
				}
				sr->Close();
			}
			
			if(version >= MinVersion && version <= MaxVersion)
			{
				listBox_files->Items->Add(files[i]);
				fileToolTips->Add("Version: " + version.ToString() + " (" + files[i]->Substring(files[i]->LastIndexOf("\\")+1) + ")");
			}

			Application::DoEvents();
		}

		array<String^>^ directories = Directory::GetDirectories(BasePath);
		for(int i=0; i<directories->Length; i++)
		{
			listFilesRecursive(directories[i], Filter, MinVersion, MaxVersion);
		}
	}

	void ecm_fix(String^ FileIn, String^ FileOut)
	{
		downgradeOptions->fileIn = FileIn;
		downgradeOptions->fileOut = FileOut;
		ECM^ ecmStructure = gcnew ECM();
		ecmStructure->Load(FileIn);
		ecmStructure->Fix(downgradeOptions);
		ecmStructure->Save(FileOut);
	}
	void smd_fix(String^ FileIn, String^ FileOut)
	{
		/*
		Encoding^ enc = Encoding::GetEncoding("GBK");
		String^ pathIn = FileIn->Substring(0, FileIn->LastIndexOf("\\")+1);
		String^ pathOut = FileOut->Substring(0, FileOut->LastIndexOf("\\")+1);

		array<STCK^>^ stcks;
		float end_sample = 0;

		// load smd
		SMD^ smd = load_smd(FileIn);

		if(smd->blocks->Length == 0)
		{
			if(!File::Exists(FileIn->Replace(".smd", ".stck")))
			{
				// unable to fix (tideborn face)
				return;
// 27 failed
			}
			else
			{
				// load stck from directory
				stcks = gcnew array<STCK^>(1);
				stcks[0] = load_stck(FileIn->Replace(".smd", ".stck"));
			}
		}
		else
		{
			if(!Directory::Exists(pathIn + enc->GetString(smd->tckPath)))
			{
				// invalid stck path
				return;
// 1 failed
			}
			else
			{
				// load stck's from smd
				stcks = gcnew array<STCK^>(smd->blocks->Length);
				for(int i=0; i<stcks->Length; i++)
				{
					stcks[i] = load_stck(pathIn + enc->GetString(smd->tckPath) + "\\" +  enc->GetString(smd->blocks[i]->stckPath));
				}
				end_sample = smd->blocks[smd->blocks->Length-1]->end_sample;
			}
		}

		// load bon
		BON^ bon = load_bon(pathIn + enc->GetString(smd->bonPath));

		smd = fix_smd(smd);
		bon = fix_bon(bon, stcks, end_sample);

		save_smd(smd, FileOut);
		save_bon(bon, pathOut + enc->GetString(smd->bonPath));
		*/
	}
	void gfx_fix(String^ FileIn, String^ FileOut)
	{
		downgradeOptions->fileIn = FileIn;
		downgradeOptions->fileOut = FileOut;
		GFX^ gfxStructure = gcnew GFX();
		gfxStructure->Load(FileIn);
		gfxStructure->Fix(downgradeOptions);
		gfxStructure->Save(FileOut);
	}
	void sgc_fix(String^ FileIn, String^ FileOut)
	{
		downgradeOptions->fileIn = FileIn;
		downgradeOptions->fileOut = FileOut;
		SGC^ sgcStructure = gcnew SGC();
		sgcStructure->Load(FileIn);
		sgcStructure->Fix(downgradeOptions);
		sgcStructure->Save(FileOut);
	}
	void bmd_fix(String^ FileIn, String^ FileOut)
	{
		downgradeOptions->fileIn = FileIn;
		downgradeOptions->fileOut = FileOut;
		BMD^ bmdStructure = gcnew BMD();
		bmdStructure->Load(FileIn);
		bmdStructure->Fix(downgradeOptions);
		bmdStructure->Save(FileOut);
	}
	void bon_fix(String^ FileIn, String^ FileOut)
	{
	}
	void ski_fix(String^ FileIn, String^ FileOut)
	{
	}
	void stck_fix(String^ FileIn, String^ FileOut)
	{
	}
	void att_fix(String^ FileIn, String^ FileOut)
	{
	}
	private: System::Void change_language(System::Object^  sender, System::EventArgs^  e)
	{
		to = comboBox_language->SelectedItem->ToString();
		select_file(nullptr, nullptr);
	}

	private: System::Void click_browse(System::Object^  sender, System::EventArgs^  e)
	{
		FolderBrowserDialog^ dir = gcnew FolderBrowserDialog();
		if(dir->ShowDialog() == Windows::Forms::DialogResult::OK && Directory::Exists(dir->SelectedPath))
		{
			if((Control^)sender == button_browseIn)
			{
				textBox_directoryIn->Text = dir->SelectedPath + "\\";
				click_loadFileList(nullptr, nullptr);
			}
			if((Control^)sender == button_browseOut)
			{
				textBox_directoryOut->Text = dir->SelectedPath + "\\";
			}
		}
	}
	private: System::Void click_loadFileList(System::Object^  sender, System::EventArgs^  e)
	{
		listBox_files->Items->Clear();

		if(Directory::Exists(textBox_directoryIn->Text) && comboBox_filter->SelectedIndex>-1 && comboBox_version->SelectedIndex>-1)
		{
			Cursor = Windows::Forms::Cursors::WaitCursor;
			fileToolTips = gcnew ArrayList();
			listBox_files->BeginUpdate();

			if(comboBox_filter->SelectedItem->ToString() == "*.ecm")
			{
				button_fix->Enabled = true;

				if(comboBox_version->SelectedItem->ToString() == "all")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), ecm_v136+1, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, ecm_v136);
				}
				if(comboBox_version->SelectedItem->ToString() == "unsupported")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), ecm_vMAX+1, 1000);
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.smd")
			{
				if(MessageBox::Show("SMD files cannot be fixed, they can only be loaded for version verification!\n\nContinue?", "Hint", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
				{
					button_fix->Enabled = false;

					if(comboBox_version->SelectedItem->ToString() == "all")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), smd_v136+1, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, smd_v136);
					}
					if(comboBox_version->SelectedItem->ToString() == "unsupported")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), smd_vMAX+1, 1000);
					}
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.bon")
			{
				if(MessageBox::Show("BON files cannot be fixed, they can only be loaded for version verification!\n\nContinue?", "Hint", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
				{
					button_fix->Enabled = false;

					if(comboBox_version->SelectedItem->ToString() == "all")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), bon_v136+1, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, bon_v136);
					}
					if(comboBox_version->SelectedItem->ToString() == "unsupported")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), bon_vMAX+1, 1000);
					}
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.ski")
			{
				if(MessageBox::Show("SKI files cannot be fixed, they can only be loaded for version verification!\n\nContinue?", "Hint", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
				{
					button_fix->Enabled = false;

					if(comboBox_version->SelectedItem->ToString() == "all")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), ski_v136+1, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, ski_v136);
					}
					if(comboBox_version->SelectedItem->ToString() == "unsupported")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), ski_vMAX+1, 1000);
					}
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.stck")
			{
				if(MessageBox::Show("STCK files cannot be fixed, they can only be loaded for version verification!\n\nContinue?", "Hint", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
				{
					button_fix->Enabled = false;

					if(comboBox_version->SelectedItem->ToString() == "all")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), stck_v136+1, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, stck_v136);
					}
					if(comboBox_version->SelectedItem->ToString() == "unsupported")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), stck_vMAX+1, 1000);
					}
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.gfx")
			{
				button_fix->Enabled = true;

				if(comboBox_version->SelectedItem->ToString() == "all")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), gfx_v136+1, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, gfx_v136);
				}
				if(comboBox_version->SelectedItem->ToString() == "unsupported")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), gfx_vMAX+1, 1000);
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.sgc")
			{
				button_fix->Enabled = true;

				if(comboBox_version->SelectedItem->ToString() == "all")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), sgc_v136+1, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, sgc_v136);
				}
				if(comboBox_version->SelectedItem->ToString() == "unsupported")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), sgc_vMAX+1, 1000);
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.att")
			{
				if(MessageBox::Show("ATT files cannot be fixed, they can only be loaded for version verification!\n\nContinue?", "Hint", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
				{
					button_fix->Enabled = false;

					if(comboBox_version->SelectedItem->ToString() == "all")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), att_v136+1, 1000);
					}
					if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, att_v136);
					}
					if(comboBox_version->SelectedItem->ToString() == "unsupported")
					{
						listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), att_vMAX+1, 1000);
					}
				}
			}

			if(comboBox_filter->SelectedItem->ToString() == "*.bmd")
			{
				button_fix->Enabled = true;

				if(comboBox_version->SelectedItem->ToString() == "all")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == ">1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), bmd_v136+1, 1000);
				}
				if(comboBox_version->SelectedItem->ToString() == "<=1.3.6")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), 0, bmd_v136);
				}
				if(comboBox_version->SelectedItem->ToString() == "unsupported")
				{
					listFilesRecursive(textBox_directoryIn->Text, comboBox_filter->SelectedItem->ToString(), bmd_vMAX+1, 1000);
				}
			}

			listBox_files->EndUpdate();

			change_Options(nullptr, nullptr);

			toolStripStatusLabel_FileCount->Text = "Number of Files: " + listBox_files->Items->Count;

			Cursor = Windows::Forms::Cursors::Default;
		}
	}
	private: System::Void select_file(System::Object^  sender, System::EventArgs^  e)
	{
		if(soap && listBox_files->SelectedItem)
		{
			Cursor = Windows::Forms::Cursors::AppStarting;

			array<String^>^ words = listBox_files->SelectedItem->ToString()->Replace(textBox_directoryIn->Text, "")->Split(gcnew array<wchar_t>{'\\'});

			for(int i=0; i<words->Length; i++)
			{
				if(words[i] == "")
				{
					words[i] = "...";
				}
			}

			array<TranslatorService::TranslateArrayResponse^>^ words_translated = soap->TranslateArray(appID, words, from, to, gcnew TranslatorService::TranslateOptions());
			textBox_translation->Text = "";
			for(int i=0; i<words_translated->Length; i++)
			{
				if(i>0)
				{
					textBox_translation->Text += " \\ ";
				}
				textBox_translation->Text += words_translated[i]->TranslatedText;
			}

			Cursor = Windows::Forms::Cursors::Default;
		}
	}

	private: System::Void doubleClick_file(System::Object^  sender, System::EventArgs^  e)
	{
		if(listBox_files->SelectedItem)
		{
			String^ options = "";
			options += " -check.if.already.open=1";
			options += " -position.maximize=1";
			options += " -toolbar.visible=1";
			options += " -line.margin.visible=1";
			options += " -line.margin.width=5";
			options += " -file.patterns.yaml=*.yaml;*.yml;*.ecm;*.gfx;*.sgc;*.att";
			options += " -lexer:YAML";
			options += " -code.page=936";
			options += " -output.code.page=936";
			options += " -character.set=134";
			options += " ";

			Diagnostics::Process::Start(Application::StartupPath + "\\SciTe.exe", options + "\"" + listBox_files->SelectedItem->ToString() + "\"");
		}
	}
	private: System::Void click_fix(System::Object^  sender, System::EventArgs^  e)
	{
		if(Directory::Exists(textBox_directoryOut->Text))
		{
			Cursor = Cursors::WaitCursor;

			for(int i=0; i<listBox_files->Items->Count; i++)
			{
				String^ fileIn = listBox_files->Items[i]->ToString();
				String^ fileOut = listBox_files->Items[i]->ToString()->Replace(textBox_directoryIn->Text, textBox_directoryOut->Text);

				// create output directory structure
				Directory::CreateDirectory(fileOut->Substring(0, fileOut->LastIndexOf("\\")));

				if(fileIn->EndsWith(".ecm"))
				{
					ecm_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".smd"))
				{
					smd_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".gfx"))
				{
					gfx_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".sgc"))
				{
					sgc_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".bmd"))
				{
					bmd_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".bon"))
				{
					bon_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".ski"))
				{
					ski_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".stck"))
				{
					stck_fix(fileIn, fileOut);
				}
				if(fileIn->EndsWith(".att"))
				{
					att_fix(fileIn, fileOut);
				}

				toolStripProgressBar->Value = i*toolStripProgressBar->Maximum/listBox_files->Items->Count;

				Application::DoEvents();
			}

			toolStripProgressBar->Value = 0;

			Cursor = Cursors::Default;
		}
	}
	private: System::Void click_analyze(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_Analyze->SelectedItem == "Verify Version")
		{
			verifyVersion();
		}
		if(comboBox_Analyze->SelectedItem == "Dump GFX Structure")
		{
			dumpGfxStructure();
		}
		if(comboBox_Analyze->SelectedItem == "Dump ECM Structure")
		{
			dumpEcmStructure();
		}
		if(comboBox_Analyze->SelectedItem == "Filter Search Pattern")
		{
			filterSearchPattern();
		}
		if(comboBox_Analyze->SelectedItem == "ECM Dependencies")
		{
			dependencies();
		}
	}

	private: void verifyVersion()
	{
		String^ Filter = comboBox_filter->SelectedItem->ToString();
		int version;
		int max = -1;

		String^ toolTip;
		for(int i=0; i<fileToolTips->Count; i++)
		{
			toolTip = ((String^)fileToolTips[i])->Substring(9);
			version = Convert::ToInt32(toolTip->Substring(0,toolTip->IndexOf(" (")));
			max = Math::Max(max, version);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.ecm")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + ecm_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.smd")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + smd_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.bon")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + bon_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.ski")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + ski_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.stck")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + stck_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.gfx")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + gfx_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.sgc")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + sgc_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.att")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + att_vMAX);
		}

		if(comboBox_filter->SelectedItem->ToString() == "*.bmd")
		{
			MessageBox::Show("Found Version: " + max + "\nMax. Supported Version: " + bmd_vMAX);
		}
	}

	private: void dependencies()
	{
		if(comboBox_filter->SelectedItem == "*.ecm" && listBox_files->SelectedIndex > -1 && File::Exists(listBox_files->SelectedItem->ToString()))
		{
			Cursor = Cursors::WaitCursor;

			TreeNode^ root = ecmDependencies(listBox_files->SelectedItem->ToString());

			(gcnew DependencyViewer(root))->Show();

			Cursor = Cursors::Default;
		}
	}
	private: bool containsNode(TreeNodeCollection^ nodes, TreeNode^ node)
	{
		for(int i=0; i<nodes->Count; i++)
		{
			// check current node
			if(nodes[i]->Text == node->Text)
			{
				return true;
			}

			// check children of current node (recursive call)
			if(nodes[i]->Nodes->Count > 0)
			{
				if(containsNode(nodes[i]->Nodes, node))
				{
					return true;
				}
			}
		}

		return false;
	}
	private: TreeNode^ ecmDependencies(String^ file)
	{
		if(File::Exists(file))
		{
			TreeNode^ node = gcnew TreeNode(file);
			TreeNode^ subNode;
			String^ basePath = file->Split(gcnew array<String^>{".pck.files"}, StringSplitOptions::None)[0];
			basePath = basePath->Substring(0, basePath->LastIndexOf("\\")+1);
			String^ subFile;

			StreamReader^ sr = gcnew StreamReader(file, Encoding::GetEncoding("GBK"));
			array<String^>^ lines = sr->ReadToEnd()->Split(gcnew array<String^>{"\r\n"}, StringSplitOptions::RemoveEmptyEntries);
			sr->Close();

			for(int i=0; i<lines->Length; i++)
			{
				if(lines[i]->StartsWith("SkinModelPath:"))
				{
					subFile = basePath + "models.pck.files\\" + lines[i]->Substring(15);
					subNode = smdDependencies(subFile);
					if(subNode)
					{
						node->Nodes->Add(subNode);
					}
				}

				if(lines[i]->StartsWith("FxFilePath:"))
				{
					subFile = basePath;

					if(lines[i]->EndsWith(".gfx"))
					{
						subFile += "gfx.pck.files\\gfx\\" + lines[i]->Substring(12);
					}
					if(lines[i]->EndsWith(".wav"))
					{
						subFile += "sfx.pck.files\\sfx\\" + lines[i]->Substring(12);
					}

					subNode = fxDependencies(subFile);

					if(subNode)
					{
//if(!containsNode(node->Nodes, subNode))
//{
	node->Nodes->Add(subNode);
//}
					}
				}

				if(lines[i]->StartsWith("AddiSkinPath:") && lines[i]->EndsWith(".ski"))
				{
					subFile = lines[i]->Substring(14);
					subNode = skiDependencies(subFile);
					if(subNode)
					{
						node->Nodes->Add(subNode);
					}
				}

				if(lines[i]->StartsWith("ChildPath:"))
				{
					subFile = basePath + "models.pck.files\\" + lines[i]->Substring(11);
					subNode = ecmDependencies(subFile);
					if(subNode)
					{
						node->Nodes->Add(subNode);
					}
				}

				if(lines[i]->StartsWith("PhysFileName:"))
				{
					subFile = file->Substring(0, file->LastIndexOf("\\")+1) + lines[i]->Substring(14);
					if(File::Exists(subFile))
					{
						node->Nodes->Add(subFile);
					}
				}
			}

			return node;
		}

		return nullptr;
	}

	private: TreeNode^ fxDependencies(String^ file)
	{
		if(File::Exists(file))
		{
			TreeNode^ node = gcnew TreeNode(file);

			if(file->EndsWith(".gfx"))
			{
				TreeNode^ subNode;
				String^ basePath = file->Split(gcnew array<String^>{".pck.files"}, StringSplitOptions::None)[0];
				basePath = basePath->Substring(0, basePath->LastIndexOf("\\")+1);
				String^ subFile;

				StreamReader^ sr = gcnew StreamReader(file, Encoding::GetEncoding("GBK"));
				array<String^>^ lines = sr->ReadToEnd()->Split(gcnew array<String^>{"\r\n"}, StringSplitOptions::RemoveEmptyEntries);
				sr->Close();

				for(int i=0; i<lines->Length; i++)
				{
					if(lines[i]->StartsWith("TexFile:"))
					{
						subFile = basePath + "gfx.pck.files\\gfx\\textures\\" + lines[i]->Substring(9);
						if(File::Exists(subFile))
						{
							node->Nodes->Add(subFile);
						}
					}

					if(lines[i]->StartsWith("Path:"))
					{
						subFile = basePath + "sfx.pck.files\\sfx\\" + lines[i]->Substring(6);
						if(File::Exists(subFile))
						{
							node->Nodes->Add(subFile);
						}
					}

					if(lines[i]->StartsWith("ModelPath:"))
					{
						subFile = basePath + "gfx.pck.files\\gfx\\models\\" + lines[i]->Substring(11);
						subNode = smdDependencies(subFile);
						if(subNode)
						{
							node->Nodes->Add(subNode);
						}
					}

					if(lines[i]->StartsWith("GfxPath:"))
					{
						subFile = basePath + "gfx.pck.files\\gfx\\" + lines[i]->Substring(9);
						subNode = fxDependencies(subFile);
						if(subNode)
						{
							node->Nodes->Add(subNode);
						}
					}

					// currently unused
					if(lines[i]->StartsWith("ShaderFile:"))
					{
						subFile = lines[i]->Substring(12);
						if(File::Exists(subFile))
						{
							node->Nodes->Add(subFile);
						}
					} 
				}

				return node;
			}
			// else ".wav"

			return node;
		}

		return nullptr;
	}

	private: TreeNode^ smdDependencies(String^ file)
	{
		if(File::Exists(file))
		{
			TreeNode^ node = gcnew TreeNode(file);
			TreeNode^ subNode;
			String^ basePath = file->Substring(0, file->LastIndexOf("\\")+1);
			String^ subFile;

			Encoding^ enc = Encoding::GetEncoding("GBK");

			SMD^ skinModel = gcnew SMD();
			skinModel->Load(file);

			subFile = basePath + enc->GetString(skinModel->SkiFile);
			subNode = skiDependencies(subFile);
			if(subNode)
			{
				node->Nodes->Add(subNode);
			}

			subFile = basePath + enc->GetString(skinModel->BonFile);
			if(File::Exists(subFile))
			{
				node->Nodes->Add(subFile);
			}

			if(skinModel->PhyFile)
			{
				subFile = basePath + enc->GetString(skinModel->PhyFile);
				if(File::Exists(subFile))
				{
					node->Nodes->Add(subFile);
				}
			}

			if(skinModel->TckPath)
			{
				subFile = basePath + enc->GetString(skinModel->TckPath);
				if(Directory::Exists(subFile))
				{
					node->Nodes->Add(subFile + "\\*.*");
				}
			}

			return node;
		}

		return nullptr;
	}

	private: TreeNode^ skiDependencies(String^ file)
	{
		if(File::Exists(file))
		{
			TreeNode^ node = gcnew TreeNode(file);
			TreeNode^ subNode;
			//String^ basePath = file->Substring(0, file->LastIndexOf("\\")+1);
			String^ subFile;

			return node;
		}

		return nullptr;
	}
	private: void dumpGfxStructure()
	{
		if(Directory::Exists(textBox_directoryOut->Text) && comboBox_filter->SelectedItem == "*.gfx")
		{
			Cursor = Cursors::WaitCursor;

			StreamReader^ sr;

			SortedList^ gfxStructure = gcnew SortedList();
			ArrayList^ gfxProperties = gcnew ArrayList();
			array<String^>^ blocks;
			array<String^>^ blockLines;
			array<wchar_t>^ seperator = gcnew array<wchar_t>{':'};
			array<String^>^ pair;
			String^ name;
			String^ value;

			// loop files
			for(int f=0; f<listBox_files->Items->Count; f++)
			{
				sr = gcnew StreamReader(listBox_files->Items[f]->ToString());
				blocks = sr->ReadToEnd()->Split(gcnew array<String^>{"GFXELEMENTID: "}, StringSplitOptions::RemoveEmptyEntries);

				// loop blocks
				for(int b=0; b<blocks->Length; b++)
				{
					blockLines = blocks[b]->Split(gcnew array<String^>{"\r\n"}, StringSplitOptions::RemoveEmptyEntries);
					value = blockLines[0];

					if(!gfxStructure->ContainsKey(value))
					{
						gfxStructure->Add(value, gcnew ArrayList());
					}

					gfxProperties = (ArrayList^)gfxStructure[value];

					// loop properties
					for(int p=1; p<blockLines->Length; p++)
					{
						if(blockLines[p]->Contains(": "))
						{
							pair = (blockLines[p]->Replace(": ", ":"))->Split(seperator);
							name = pair[0];
							value = pair[1];
/*
							if(name == "CtrlType")
							{
								name += ": " + value;
							}
*/
							if(!gfxProperties->Contains(name))
							{
								gfxProperties->Add(name);
							}
						}
						else
						{
							//
						}
					}
				}

				sr->Close();

				Application::DoEvents();
			}

			StreamWriter^ sw = gcnew StreamWriter(textBox_directoryOut->Text + "\\modfix_devscan_" + comboBox_filter->Items[comboBox_filter->SelectedIndex]->ToString()->Substring(2) + "_commands.txt");

			for(int i=0; i<gfxStructure->Count; i++)
			{
				String^ key = (String^)gfxStructure->GetKey(i);
				sw->WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++");
				if(!key->StartsWith("MOXT"))
				{
					sw->Write("GFXELEMENTID: ");
				}
				sw->WriteLine(key);
				sw->WriteLine("++++++++++++++++++++++++++++++++++++++++++++++++++");

				gfxProperties = (ArrayList^)gfxStructure[key];

				for(int p=0; p<gfxProperties->Count; p++)
				{
					sw->WriteLine((String^)gfxProperties[p] + ":");
				}
			}

			sw->Close();

			Cursor = Cursors::Default;
		}
		else
		{
			MessageBox::Show("Select an output directory and select a filter");
		}
	}

	private: void dumpEcmStructure()
	{
		if(Directory::Exists(textBox_directoryOut->Text) && comboBox_filter->SelectedItem == "*.ecm")
		{
			Cursor = Cursors::WaitCursor;

			StreamReader^ sr;

			ArrayList^ evttypes = gcnew ArrayList();
			array<String^>^ lines;

			// loop files
			for(int f=0; f<listBox_files->Items->Count; f++)
			{
				sr = gcnew StreamReader(listBox_files->Items[f]->ToString());
				lines = sr->ReadToEnd()->Split(gcnew array<String^>{"\r\n"}, StringSplitOptions::RemoveEmptyEntries);
				sr->Close();

				for(int i=0; i<lines->Length; i++)
				{
					if(lines[i]->StartsWith("EventType:") && !evttypes->Contains(lines[i]))
					{
						evttypes->Add(lines[i]);
					}
				}
			}

			Cursor = Cursors::Default;
		}
	}
	private: void filterSearchPattern()
	{
		if(/*Directory::Exists(textBox_directoryOut->Text) && */textBox_Analyze->Text != "")
		{
			if(comboBox_filter->SelectedItem->ToString() == "*.smd" || comboBox_filter->SelectedItem->ToString() == "*.bon" || comboBox_filter->SelectedItem->ToString() == "*.ski" || comboBox_filter->SelectedItem->ToString() == "*.stck")
			{
				MessageBox::Show("Not available for selected filetype!");
				return;
			}

			Cursor = Cursors::WaitCursor;

			ArrayList^ files = gcnew ArrayList();
			ArrayList^ toolTips = gcnew ArrayList();

			for(int i=0; i<listBox_files->Items->Count; i++)
			{
				StreamReader^ sr = gcnew StreamReader(listBox_files->Items[i]->ToString());

				if(sr->ReadToEnd()->Contains(textBox_Analyze->Text))
				{
					files->Add(listBox_files->Items[i]->ToString());
					toolTips->Add((String^)fileToolTips[i]);
				}
				sr->Close();
			}

			listBox_files->Items->Clear();
			fileToolTips->Clear();

			listBox_files->Items->AddRange(files->ToArray());
			fileToolTips = toolTips;

			toolStripStatusLabel_FileCount->Text = "Number of Files: " + listBox_files->Items->Count;

			Cursor = Cursors::Default;
		}
		else
		{
			MessageBox::Show("Enter a text");
		}
	}
	private: System::Void check_Translator(System::Object^  sender, System::EventArgs^  e)
	{
		if(checkBox_Translator->Checked)
		{
			Cursor = Windows::Forms::Cursors::WaitCursor;
			LoadingScreen^ initialize = gcnew LoadingScreen();
			initialize->Show();
			Application::DoEvents();
			try
			{
				soap = gcnew TranslatorService::SoapService();
				appID = "763743C8043FA427227700179E653860B731D443";
				from = "zh-CHS";
				to = "en";
				comboBox_language->Items->AddRange(soap->GetLanguagesForTranslate(appID));
				comboBox_language->SelectedItem = "en";

				textBox_translation->Enabled = true;
				comboBox_language->Enabled = true;
			}
			catch(Exception^ e)
			{
				textBox_translation->Text = "TRANSLATION SERVICE UNAVAILABLE";
				MessageBox::Show(e->Message);
				checkBox_Translator->Checked = false;
			}
			initialize->Close();
			Cursor = Windows::Forms::Cursors::Default;
		}
		else
		{
			soap = nullptr;
			textBox_translation->Enabled = false;
			comboBox_language->Enabled = false;
		}
	}
	private: System::Void change_AnalyzeType(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_Analyze->SelectedItem == "Filter Search Pattern")
		{
			textBox_Analyze->Enabled = true;
		}
		else
		{
			textBox_Analyze->Enabled = false;
		}
	}
	private: System::Void change_Options(System::Object^  sender, System::EventArgs^  e)
	{
		downgradeOptions->gfxDowngrade = true;
		downgradeOptions->gfx152to150 = checkBox_gfxChonvert152->Checked;
		downgradeOptions->gfx210to160 = checkBox_gfxConvert210->Checked;
		downgradeOptions->ecmDowngrade = true;
		downgradeOptions->ecmSoulsphereHook = checkBox_ecmHook->Checked;
		downgradeOptions->ecmSoulsphereHookTX = -0.3;
		downgradeOptions->ecmSoulsphereHookTY = -0.125;
		downgradeOptions->ecmSoulsphereHookTZ = 0.15;
		downgradeOptions->sgcDowngrade = true;
	}
	private: System::Void click_Copy(System::Object^  sender, System::EventArgs^  e)
	{
		if(listBox_files->SelectedIndex > -1)
		{
			String^ s = listBox_files->SelectedItem->ToString();
			if(s->EndsWith(".gfx"))
			{
				s = s->Substring(s->IndexOf("\\gfx\\")+5)->Replace("\\", "/");
			}
			Clipboard::SetText(s);
		}
	}
	private: System::Void mouseMove_toolTip(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		int i = listBox_files->IndexFromPoint(listBox_files->PointToClient(MousePosition));
		if(i>=0 && i<listBox_files->Items->Count)
		{
			String^ text = (String^)fileToolTips[i];

			if(mouseMoveCheck->X != e->X || mouseMoveCheck->Y != e->Y)
			{
				toolTip1->SetToolTip((Control^)sender, text);
				mouseMoveCheck->X = e->X;
				mouseMoveCheck->Y = e->Y;
			}
		}
		else
		{
			toolTip1->Hide(listBox_files);
		}
	}
};