#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Patient {
public:
    int id;
    string name;
    int age;
    string gender;
    string contact;
    string medicalHistory;

    void input() {
        cout << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender: ";
        cin >> gender;
        cout << "Enter Contact Information: ";
        cin.ignore();
        getline(cin, contact);
        cout << "Enter Medical History: ";
        getline(cin, medicalHistory);
    }
    void display() {
        const string red = "\033[31m";
        const string reset = "\033[0m";

        cout << red;
        cout << "Patient ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Contact: " << contact << endl;
        cout << "Medical History: " << medicalHistory << endl;
        cout << reset;
    }


};
class Appointment {
public:
    int patientId;
    string doctorName;
    string date;
    string time;

    void input() {
        cout << "Enter Patient ID: ";
        cin >> patientId;
        cout << "Enter Doctor's Name: ";
        cin.ignore();
        getline(cin, doctorName);
        cout << "Enter Appointment Date (DD/MM/YYYY): ";
        getline(cin, date);
        cout << "Enter Appointment Time (HH:MM): ";
        getline(cin, time);
    }

    void display() {
        cout << "Patient ID: " << patientId << endl;
        cout << "Doctor: " << doctorName << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
    }
};

vector<Patient> patients;
vector<Appointment> appointments;

void loadPatients() {
    ifstream file("patients.txt");
    if (file.is_open()) {
        Patient patient;
        while (file >> patient.id) {
            file.ignore();
            getline(file, patient.name);
            file >> patient.age >> patient.gender;
            file.ignore();
            getline(file, patient.contact);
            getline(file, patient.medicalHistory);
            patients.push_back(patient);
        }
        file.close();
    }
}

void savePatients() {
    ofstream file("patients.txt");
    for (auto &patient : patients) {
        file << patient.id << endl;
        file << patient.name << endl;
        file << patient.age << endl;
        file << patient.gender << endl;
        file << patient.contact << endl;
        file << patient.medicalHistory << endl;
    }
    file.close();
}

void loadAppointments() {
    ifstream file("appointments.txt");
    if (file.is_open()) {
        Appointment appointment;
        while (file >> appointment.patientId) {
            file.ignore();
            getline(file, appointment.doctorName);
            getline(file, appointment.date);
            getline(file, appointment.time);
            appointments.push_back(appointment);
        }
        file.close();
    }
}

void saveAppointments() {
    ofstream file("appointments.txt");
    for (auto &appointment : appointments) {
        file << appointment.patientId << endl;
        file << appointment.doctorName << endl;
        file << appointment.date << endl;
        file << appointment.time << endl;
    }
    file.close();
}

void registerPatient() {
    Patient newPatient;
    newPatient.id = patients.size() + 1;
    newPatient.input();
    patients.push_back(newPatient);
    savePatients();
    cout << "Patient Registered with ID: " << newPatient.id << endl;
}

void scheduleAppointment() {
    Appointment newAppointment;
    newAppointment.input();
    appointments.push_back(newAppointment);
    saveAppointments();
    cout << "Appointment Scheduled for Patient ID: " << newAppointment.patientId << endl;
}

void viewPatients() {
    for (auto &patient : patients) {
        patient.display();
        cout << "----------------------" << endl;
    }
}

void viewAppointments() {
    for (auto &appointment : appointments) {
        appointment.display();
        cout << "----------------------" << endl;
    }
}

void updatePatientRecord() {
    int id;
    cout << "Enter Patient ID to update: ";
    cin >> id;
    for (auto &patient : patients) {
        if (patient.id == id) {
            patient.input();
            savePatients();
            cout << "Patient record updated." << endl;
            return;
        }
    }
    cout << "Patient ID not found." << endl;
}

int main() {
    loadPatients();
    loadAppointments();

    int choice;
    do {
        cout << "Hospital Management System" << endl;
        cout << "1. Register New Patient" << endl;
        cout << "2. Schedule Appointment" << endl;
        cout << "3. View Patients" << endl;
        cout << "4. View Appointments" << endl;
        cout << "5. Update Patient Record" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {
            case 1:
                registerPatient();
            break;
            case 2:
                scheduleAppointment();
            break;
            case 3:
                viewPatients();
            break;
            case 4:
                viewAppointments();
            break;
            case 5:
                updatePatientRecord();
            break;
            case 6:
                cout << "Exiting..." << endl;
            break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}