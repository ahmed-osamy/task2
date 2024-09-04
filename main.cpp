#include <bits/stdc++.h>
using namespace std;
class Person
{
protected:
    string name;
    int age;

public:
    Person() : name(""), age(0) {}
    Person(string name, int age) : name(name), age(age) {}
    virtual ~Person() {}

    virtual void display() const
    {
        cout << "name: " << name << ", age: " << age << endl;
    }
};
class Patient : public Person
{
    int patientId;
    string diagnosis;

public:
    Patient(string name, int age, int patientId, string diagnosis)
        : Person(name, age), patientId(patientId), diagnosis(diagnosis) {}

    void display() const
    {
        Person::display();
        cout << "patient id: " << patientId << ", diagnosis: " << diagnosis << endl;
    }

    int getPatientId() const
    {
        return patientId;
    }
};
class Doctor : public Person
{
    int doctorId;
    string specialization;

public:
    Doctor(string name, int age, int doctorId, string specialization)
        : Person(name, age), doctorId(doctorId), specialization(specialization) {}

    void display() const
    {
        Person::display();
        cout << "doctor id: " << doctorId << ", specialization: " << specialization << endl;
    }

    int getDoctorId() const
    {
        return doctorId;
    }
};
class Appointment
{
private:
    const Patient* patient;
    const Doctor* doctor;
    string date;

public:
    Appointment() : patient(NULL), doctor(NULL), date("") {}
    Appointment(const Patient* p, const Doctor* d, string date) : patient(p), doctor(d), date(date) {}

    void Display() const
    {
        if (patient != NULL && doctor != NULL)
        {
            cout << "appointment details:"<<endl;
            patient->display();
            doctor->display();
            cout << "date: " << date << endl;
        }
    }
};
class Hospital
{
private:
    Patient** patients;
    Doctor** doctors;
    Appointment** appointments;
    int numPatients;
    int numDoctors;
    int numAppointments;
    int maxPatients;
    int maxDoctors;
    int maxAppointments;

    void resizePatients()
    {
        maxPatients *= 2;
        Patient** newPatients = new Patient*[maxPatients];
        for (int i = 0; i < numPatients; ++i)
        {
            newPatients[i] = patients[i];
        }
        delete[] patients;
        patients = newPatients;
    }

    void resizeDoctors()
    {
        maxDoctors *= 2;
        Doctor** newDoctors = new Doctor*[maxDoctors];
        for (int i = 0; i < numDoctors; ++i)
        {
            newDoctors[i] = doctors[i];
        }
        delete[] doctors;
        doctors = newDoctors;
    }

    void resizeAppointments()
    {
        maxAppointments *= 2;
        Appointment** newAppointments = new Appointment*[maxAppointments];
        for (int i = 0; i < numAppointments; ++i)
        {
            newAppointments[i] = appointments[i];
        }
        delete[] appointments;
        appointments = newAppointments;
    }

    const Patient* findPatient(int id) const
    {
        for (int i = 0; i < numPatients; ++i)
        {
            if (patients[i]->getPatientId() == id)
            {
                return patients[i];
            }
        }
        return NULL;
    }

    const Doctor* findDoctor(int id) const
    {
        for (int i = 0; i < numDoctors; ++i)
        {
            if (doctors[i]->getDoctorId() == id)
            {
                return doctors[i];
            }
        }
        return NULL;
    }

public:
    Hospital() : numPatients(0), numDoctors(0), numAppointments(0),
        maxPatients(10), maxDoctors(10), maxAppointments(10)
    {
        patients = new Patient*[maxPatients];
        doctors = new Doctor*[maxDoctors];
        appointments = new Appointment*[maxAppointments];
    }

    ~Hospital()
    {
        for (int i = 0; i < numPatients; ++i)
        {
            delete patients[i];
        }
        delete[] patients;

        for (int i = 0; i < numDoctors; ++i)
        {
            delete doctors[i];
        }
        delete[] doctors;

        for (int i = 0; i < numAppointments; ++i)
        {
            delete appointments[i];
        }
        delete[] appointments;
    }

    void addPatient(const string& name, int age, int id, const string& diagnosis)
    {
        if (numPatients >= maxPatients)
        {
            resizePatients();
        }
        patients[numPatients++] = new Patient(name, age, id, diagnosis);
    }

    void addDoctor(const string& name, int age, int id, const string& specialization)
    {
        if (numDoctors >= maxDoctors)
        {
            resizeDoctors();
        }
        doctors[numDoctors++] = new Doctor(name, age, id, specialization);
    }

    void scheduleAppointment(int patientId, int doctorId, const string& date)
    {
        const Patient* p = findPatient(patientId);
        const Doctor* d = findDoctor(doctorId);

        if (p != NULL && d != NULL)
        {
            if (numAppointments >= maxAppointments)
            {
                resizeAppointments();
            }
            appointments[numAppointments++] = new Appointment(p, d, date);
        }
        else
        {
            cout << "patient or doctor not found!" << endl;
        }
    }

    void displayAppointments() const
    {
        for (int i = 0; i < numAppointments; ++i)
        {
            appointments[i]->Display();
            cout << "---------------------------"<<endl;
        }
    }
};

int main()
{
    Hospital hospital
    hospital.addPatient("ahmed", 21, 101, "deprssion");
    hospital.addPatient("sam", 21, 201, "heart disease");
    hospital.addDoctor("samo", 21, 102, "psychiatrist");
    hospital.addDoctor("osamy", 21, 202, "Cardiologist");
    hospital.scheduleAppointment(1, 1, "2024-09-05");
    hospital.scheduleAppointment(2, 2, "2024-09-06");
    hospital.displayAppointments();

    return 0;
}
