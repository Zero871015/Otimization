#pragma once
#include "Polynomial.h"
#include "Golden.h"
#include "Powell.h"
#include "Newton.h"
#include "Quasi.h"
#include "Exceptions.h"
#include "SteepDescent.h"
#include "ConjugateGradient.h"
#include <vector>


namespace Project2EM {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>

	std::vector<Polynomial> polys;
	std::map < std::string, double > startPoint;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::Button^  button3;






	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->InitialDirectory = L"D:\\Visual Studio\\Project2_EM\\Otimization\\Project2_EM";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 82);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(407, 206);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 313);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(760, 292);
			this->textBox2->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(407, 35);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Read File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 64);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 15);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Input Data";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 295);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 15);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Output";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(425, 82);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox3->Size = System::Drawing::Size(191, 206);
			this->textBox3->TabIndex = 0;
			this->textBox3->Text = L"initial point : [x]\r\n = [50]\r\ninterval :\r\nx = [0 ,70 ]";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(422, 64);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 15);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Parameter Input";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(425, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(347, 35);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Compute";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->Cursor = System::Windows::Forms::Cursors::Default;
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(622, 100);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(149, 23);
			this->comboBox1->TabIndex = 5;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(623, 82);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(72, 15);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Polynomial";
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Powell’s Method ", L"Newton Method ", L"Steep Descent Algorithm ",
					L"Quasi-Newton Method ", L"Conjugate Gradient Methods "
			});
			this->comboBox2->Location = System::Drawing::Point(622, 197);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(149, 23);
			this->comboBox2->TabIndex = 5;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(623, 179);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(51, 15);
			this->label5->TabIndex = 6;
			this->label5->Text = L"Method";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(622, 251);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(149, 37);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Save";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 617);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->ShowDialog();
	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		
		textBox1->Clear();
		comboBox1->Items->Clear();
		StreamReader^ file = gcnew StreamReader(openFileDialog1->FileName);
		String^ str = file->ReadToEnd();
		textBox1->Text += str;
		array<String^>^ temp = str->Split(gcnew array<System::String ^>{" ", "\n", "\t","\r"}, System::StringSplitOptions::RemoveEmptyEntries);
		
		for each (auto var in temp)
		{
			//convert C# String to c++ std::string.
			using System::Runtime::InteropServices::Marshal;
			System::IntPtr pointer = Marshal::StringToHGlobalAnsi(var);
			char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
			std::string returnString(charPointer, var->Length);
			Marshal::FreeHGlobal(pointer);

			Polynomial p(returnString);
			polys.push_back(p);
			
			comboBox1->Items->Add(var);
		}

		
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		std::map<std::string, double> m;
		std::map<std::string, double> min;
		std::map<std::string, double> max;

		System::String^ outputdata = gcnew System::String("");
		std::string input_par = "";
		int l_parentheses = 0;
		int r_parentheses = 0;
		int next = 0;

		std::vector<std::string> data_d; //initial data
		std::vector<std::string> data_s; // parameter name
		input_par = LoadStartPoint();
		/*	std::cout << temp_s << std::endl;*/

		if (input_par.find("initial") != -1)
		{
			r_parentheses = input_par.find("]", next);
			//get parameter name
			for (l_parentheses = input_par.find("[", next); l_parentheses < r_parentheses; l_parentheses = next)
			{
				std::string temp = "";
				next = input_par.find(",", next + 1);
				if (next >= r_parentheses || next == -1)
				{
					next = r_parentheses;
				}
				temp += input_par.substr(l_parentheses + 1, next - l_parentheses - 1);
				data_s.push_back(temp);
			}

			r_parentheses = input_par.find("]", next + 1);
			//get parameter initial point
			for (l_parentheses = input_par.find("[", next); l_parentheses < r_parentheses; l_parentheses = next)
			{
				std::string temp = "";
				next = input_par.find(",", next + 1);
				if (next >= r_parentheses || next == -1)
				{
					next = r_parentheses;
				}
				temp += input_par.substr(l_parentheses + 1, next - l_parentheses - 1);
				data_d.push_back(temp);
			}

			//initial value insert
			for (int i = 0; i < (int)data_s.size(); i++)
			{
				m[data_s[i]] = std::stod(data_d[i]);
			}
		}

		if (input_par.find("interval") != -1)
		{
			next = input_par.find("\n", next + 1);
			//get interval
			for (int i = 0; i < (int)data_s.size(); i++)
			{
				std::string par_name = "";
				next = input_par.find("\n", next + 1);
				r_parentheses = input_par.find("]", next + 1);
				l_parentheses = input_par.find("[", next);


				par_name = input_par.substr(next + 1, input_par.find("=", next) - next - 1);
				next = input_par.find(",", next + 1);
				for (int j = 0; j < (int)par_name.length(); j++)
				{
					if (par_name[j] == ' ')
						par_name.erase(par_name.begin() + j--);
				}
				min[par_name] = stod(input_par.substr(l_parentheses + 1, next - l_parentheses - 1));
				max[par_name] = stod(input_par.substr(next + 1, r_parentheses - next - 1));

			}
		}

		try
		{
			if (comboBox2->SelectedIndex == 0)
				outputdata = Powell(polys[comboBox1->SelectedIndex], m, min, max);
			else if (comboBox2->SelectedIndex == 1)
				outputdata = Newton(polys[comboBox1->SelectedIndex], m);
			else if (comboBox2->SelectedIndex == 2)
				outputdata = SteepDescent(polys[comboBox1->SelectedIndex], m, min, max);
			else if (comboBox2->SelectedIndex == 3)
				outputdata = QuasiNewton(polys[comboBox1->SelectedIndex], m);
			else if (comboBox2->SelectedIndex == 4)
				outputdata = ConjugateGradient(polys[comboBox1->SelectedIndex], m, min, max);
			textBox2->Text = outputdata;

		}
		catch (Exceptions e)
		{
			switch (e.getType())
			{
			case error::dimension:
				std::cout << "Dimension not equal!" << std::endl;
				textBox2->Text = "Dimension not equal!";
				break;
			case error::divideZero:
				std::cout << "Divide 0!" << std::endl;
				textBox2->Text = "Divide 0!";
				break;
			case error::rowNotEqualCol:
				std::cout << "Row is not equal col." << std::endl;
				textBox2->Text = "Row is not equal col.";
				break;
			case error::noInverse:
				std::cout << "No inverse." << std::endl;
				textBox2->Text = "No inverse.";
				break;
			case error::done:
				break;
			case error::computeError:
				std::cout << "Compute error." << std::endl;
				textBox2->Text = "Compute error.";
				break;
			default:
				std::cout << "wrong";
				textBox2->Text = "wrong";
				break;
			}
		}
		catch (...)
		{
			textBox2->Text = "error";
		}
	}

	std::string LoadStartPoint()
	{
		std::string str;

		//convert C# String to c++ std::string.
		using System::Runtime::InteropServices::Marshal;
		System::IntPtr pointer = Marshal::StringToHGlobalAnsi(textBox3->Text);
		char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
		std::string returnString(charPointer, textBox3->Text->Length);
		Marshal::FreeHGlobal(pointer);
		return returnString;
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	StreamWriter ^ sw = gcnew StreamWriter("output.txt");
	sw->Write(textBox2->Text);
	sw->Close();
}
};
}
