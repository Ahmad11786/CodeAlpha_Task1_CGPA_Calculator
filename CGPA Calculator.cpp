#include<iostream>
#include<string>
#include<iomanip>
#include<cctype>
using namespace std;
const int Max_sem=10;
const int Max_courses=9;
struct Course {
	string subject, s_grade;
	int c_credit_h;
	float point;
};
struct Semester {
	int semester_n;
	int t_credit_h=0;
	Course course[Max_sem];
	int t_course=0;
	float t_gradepoint;
	double gpa=0;
};
float getgradepoint(string &grade) {
	for (char &c : grade) c = toupper(c);
	if (grade == "A+" || grade == "A") return 4.0;
	if (grade == "A-") return 3.7;
	if (grade == "B+") return 3.3;
	if (grade == "B") return 3.0;
	if (grade == "B-") return 2.7;
	if (grade == "C+") return 2.3;
	if (grade == "C") return 2.0;
	if (grade == "C-") return 1.7;
	if (grade == "D+") return 1.3;
	if (grade == "D") return 1.0;
	if (grade == "F") return 0.0;

	return -1.0;
}
Semester take_semester(int i) {
	Semester semest;
	semest.semester_n = i;
	semest.t_course = 0;
	semest.t_credit_h = 0;
	semest.t_gradepoint=0;

	cout<<"\n========================================================\n";
	cout<<"                 Semester  : "<<i<<endl;
	cout<<"========================================================\n";
again:
	cout<<"Enter number of courses (max courses per semester "<<Max_courses<<" ) : ";
	cin>>semest.t_course;
	if(semest.t_course > Max_courses || semest.t_course<=0) {
		cout<<"Invalid ........\n";
		goto again;
	}
	cin.ignore();
	for(int j=0; j<semest.t_course; j++) {
		cout<<"\n================ Course "<<j+1<<" ================\n";
		cout<<"Course name (optional) : ";
		getline(cin,semest.course[j].subject);
		cout<<"Course Grade (A,A+,B,D,F.. ) : ";
		getline(cin,semest.course[j].s_grade);
	credit:	cout<<"Credit Hourse : ";

		if(	!(cin>>semest.course[j].c_credit_h)) {

			cout << "Invalid..!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			goto credit;
		}
		if(semest.course[j].c_credit_h<0)
		{
			cout<<"Invalid.....\n";
			goto credit;
		}

		cin.ignore();

		semest.course[j].point=getgradepoint(semest.course[j].s_grade);
		while(semest.course[j].point == -1.0) {
			cout<<"Invalid grade ! \n";
			cout<<"\n Please enter again Grade (A,A+,B,D,F.. ) : ";
			getline(cin,semest.course[j].s_grade);
			semest.course[j].point=getgradepoint(semest.course[j].s_grade);
		}

		semest.t_credit_h += semest.course[j].c_credit_h;
		semest.t_gradepoint +=(semest.course[j].c_credit_h * semest.course[j].point );
	}

	semest.gpa = (semest.t_credit_h>0)? (semest.t_gradepoint/semest.t_credit_h) : 0.0;
	return semest;
}

void displaysemest(const Semester &semest) {
	cout << "\n============================================================================" << endl;
	cout << "            Semester " << semest.semester_n << " Course Details" << endl;
	cout << "==============================================================================" << endl;
	cout << left << setw(25) << "Course Name"
	     << right << setw(10) << "Credits"
	     << right << setw(12) << "Grade"
	     << right << setw(15) << "Grade Points" << endl;

	cout << "------------------------------------------------------------------------------" << endl;

	cout << fixed << setprecision(2);

	for(int i = 0; i < semest.t_course; i++) {
		cout << left << setw(25) << semest.course[i].subject
		     << right << setw(10) << semest.course[i].c_credit_h
		     << right << setw(12) << semest.course[i].s_grade
		     << right << setw(15) << semest.course[i].point
		     << endl;
	}
	cout << "==============================================" << endl;
}
int main() {
	int sem;
	double Total_Credit = 0;
	double Total_Gradepoint = 0;
	double cgpa;
	cout<<"----------------------- CGPA Calculator -----------------------\n";
again:
	cout<<"Enter semester no.(max semester 1-"<<Max_sem<<" ) : ";
	cin>>sem;
	if(sem>Max_sem|| sem<= 0) {
		cout<<"Invalid Semester..! \n";
		goto again;
	}
	Semester semester[Max_sem];
	for(int i=0; i<sem; i++) {
		semester[i]=take_semester(i+1);
	}
	cout << "\n\n============= RESULTS =============\n";
	for (int i = 0; i < sem; i++) {
		displaysemest(semester[i]);
	}
	for(int i =0 ; i<sem; i++) {
		Total_Credit +=semester[i].t_credit_h;
		Total_Gradepoint += semester[i].t_gradepoint;
	}
	cgpa = (Total_Credit > 0 )?  (Total_Gradepoint / Total_Credit) : 0.0;

	cout << "\n========================================\n";
	cout << "         OVERALL CGPA\n";
	cout << "========================================\n";
	cout << "Total Credits: " << Total_Credit << "\n";
	cout << "************** CGPA: " << fixed << setprecision(2) << cgpa << " **************\n";
	cout << "========================================\n";

	return 0;

}

