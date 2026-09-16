#include <iostream> 
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

class Person {
protected:
	string fullName;
	int height;
	int weight;
	string gender;
	string country;
	string email;
public:
	Person() : fullName("Невідомо"), height(0), weight(0), gender("Невідомо"), country("Не вказано"), email("Відсутнє") {}
	Person(const string& fn, int h, int w, const string& g, const string& c, const string& email) :fullName(fn), height(h), weight(w), gender(g), country(c), email(email) {
		if (h < 0) {
			throw invalid_argument("Від'ємний зріст!");
		}
		if (w < 0) {
			throw invalid_argument("Від'ємна вага!!");
		}
	}

	bool height_above_200() const {
		return height > 200;
	}
	bool live_in_Ukraine() const {
		return (country == "Ukraine" || country == "Україна");
	}
	void changeEmail(const string& e) {
		email = e;
	}
	virtual void print() const {
		cout << "\nПІБ: " << fullName << "\nЗріст: " << height << "\nВага: " << weight << "\nСтать: " << gender << "\nКраїна: " << country << "\nEmail: " << email << "\n";
	}
	void printName() const {
		cout << fullName;
	}

	virtual ~Person() = default;

};

class Worker : public Person {
	string factory;
	string position;
	int salary;
public:
	Worker(const string& fn, int h, int w, const string& g, const string& c, const string& email, const string& fact, const string& pos, int salary) : Person(fn, h, w, g, c, email), factory(fact), position(pos), salary(salary) {}

	void increaseSalary() {
		if (position == "Assembler") {
			salary += 1000;
		}
		else if (position == "Operator") {
			salary += 1500;
		}
		else if (position == "Machinist") {
			salary += 1750;
		}
		else if (position == "Supervisor") {
			salary += 2500;
		}
		else if (position == "Director") {
			salary += 3000;
		}
		else return;
	}
	void changePos(const string& pos) {
		position = pos;
	}
	void print() const override {
		cout << "\nПІБ: " << fullName << "\nЗріст: " << height << "\nВага: " << weight << "\nСтать: " << gender << "\nКраїна: " << country << "\nEmail: " << email << "\nЗавод: " << factory << "\nПосада: " << position << "\nОклад: " << salary << "\n";
	}
};

class Object {
	int reqExperience;
	int reqRank;
	string name;
public:
	Object(int reqExp, int reqRank, const string name) : reqExperience(reqExp), reqRank(reqRank), name(name) {}

	int returnReqExperience() {
		return reqExperience;
	}
	int returnReqRank() {
		return reqRank;
	}
	string returnName() {
		return name;
	}
};

class Electrician : public Person {
	int experience;
	int rank;
	Object* currentObject;
public:
	Electrician(const string& fn, int h, int w, const string& g, const string& c, const string& email, int exp, int rank, Object* currObj) : Person(fn, h, w, g, c, email), experience(exp), rank(rank), currentObject(currObj) {}

	bool meetRequirements() {
		return (experience >= currentObject->returnReqExperience() && rank >= currentObject->returnReqRank());
	}
	bool meetRequirements(Object* object) {
		return (experience >= object->returnReqExperience() && rank >= object->returnReqRank());
	}
	void changeObject(Object* newObject) {
		currentObject = newObject;
	}
	void print() const override {
		cout << "\nПІБ: " << fullName << "\nЗріст: " << height << "\nВага: " << weight << "\nСтать: " << gender << "\nКраїна: " << country << "\nEmail: " << email << "\nСтаж: " << experience << "\nРозряд: " << rank << "\nОбьект: " << currentObject->returnName() << "\n";
	}
};

void gui() {
	cout << "\nОберіть:";
	cout << "\n1.Вивести інформацію про людину";
	cout << "\n2.Додати людину";
	cout << "\n3.Видалити людину";
	cout << "\n4.Додати об'єкт";
	cout << "\n5.Змінити email";
	cout << "\n6.Дії з робітником";
	cout << "\n7.Дії з електриком";
	cout << "\n8.Вивести електриків, які можуть працювати на об'єкті";
	cout << "\n0.Вихід\n";
}

void choicePerson(const vector<Person*>& vec) {
	cout << "\n";
	for (int i = 0; i < vec.size(); i++) {
		cout << i + 1 << ".";
		vec[i]->printName();
		cout << "\n";
	}
	cout << "0.Вихід\n";
}

void addPerson() {
	cout << "\nКого ви хочете добавити?";
	cout << "\n1.Звичайну людину";
	cout << "\n2.Робітника";
	cout << "\n3.Електрика";
	cout << "\n0.Вихід\n";
}

void choiceObject(const vector<Object*>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << i + 1 << "." << vec[i]->returnName() << "\n";
	}
}

bool choiceCheck(int& value) {
	if (!(std::cin >> value)) {
		cin.clear();
		cin.ignore(10000, '\n');
		return false;
	}
	else return true;
}

int main() {
	vector<Person*> People;
	vector<Object*> Objects;

	Objects.push_back(new Object(8, 6, "Комсомол"));

	People.push_back(new Person("Орєшин Максим Олегович", 152, 70, "Чоловік", "Україна", "maksym.orechin11@gmail.com"));

	People.push_back(new Worker("Гуменнмй Дмитро Юрійович", 180, 80, "Чоловік", "Україна", "gumennynumber1@gmail.com", "Сахарний завод", "Machinist", 31000));

	People.push_back(new Electrician("Колоколов Павло Афанасійович", 190, 100, "Чоловік", "Польша", "kolokolov12@gmail.com", 10, 8, Objects[0]));


	while (true) {
		gui();

		int choice;
		if (!choiceCheck(choice)) {
			cout << "\nВведіть число!\n";
			continue;
		}

		switch (choice) {
		case 1: {
			if (People.size() == 0) {
				cout << "\nСписок порожній!\n";
				break;
			}

			choicePerson(People);

			int personChoice;
			if (!choiceCheck(personChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}
			if (personChoice == 0)
				break;
			if (personChoice < 1 || personChoice > People.size()) {
				cout << "\nТакої людини немає!\n";
				break;
			}

			People[personChoice - 1]->print();
			break;
		}
		case 2: {
			string fullName;
			int height;
			int weight;
			string gender;
			string country;
			string email;

			addPerson();

			int addPersonChoice;
			if (!choiceCheck(addPersonChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}
			if (addPersonChoice == 0)
				break;
			if (addPersonChoice < 1 || addPersonChoice > 3) {
				cout << "\nНевірний вибір!\n";
				break;
			}

			cout << "\nВведіть ім'я: ";
			cin.ignore();
			getline(cin, fullName);

			cout << "Введіть зріст: ";
			cin >> height;
			while (cin.fail() || height < 0) {
				cout << "Невірний зріст! Введіть ще раз: ";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> height;
			}

			cout << "Введіть вагу: ";
			cin >> weight;

			while (cin.fail() || weight < 0) {
				cout << "Невірна вага! Введіть ще раз: ";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> weight;
			}

			cout << "Введіть стать(Чоловік/Жінка): ";
			cin >> gender;
			while (gender != "Чоловік" && gender != "Жінка") {
				cout << "Введіть Чоловік або Жінка: ";
				cin >> gender;
			}

			cout << "Введіть країну: ";
			cin.ignore();
			getline(cin, country);

			cout << "Введіть email: ";
			cin >> email;

			if (addPersonChoice == 1) {
				People.push_back(
					new Person(fullName, height,weight,gender, country, email)
				);
				cout << "\nЛюдину додано!\n";
			}
			else if (addPersonChoice == 2) {
				string factory;
				string position;
				int salary;

				cout << "Введіть завод: ";
				cin.ignore();
				getline(cin, factory);

				cout << "Введіть посаду: ";
				getline(cin, position);

				cout << "Введіть оклад: ";
				cin >> salary;
				while (cin.fail() || salary < 0) {
					cout << "Невірний оклад! Введіть ще раз: ";
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> salary;
				}

				People.push_back(new Worker(fullName, height, weight, gender, country, email, factory, position, salary));
				cout << "\nРобітника додано!\n";
			}
			else if (addPersonChoice == 3) {
				int experience;
				int rank;

				cout << "Введіть стаж: ";
				cin >> experience;
				while (cin.fail() || experience < 0) {
					cout << "Невірний стаж! Введіть ще раз: ";
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> experience;
				}

				cout << "Введіть розряд: ";
				cin >> rank;
				while (cin.fail() || rank < 0) {
					cout << "Невірний розряд! Введіть ще раз: ";
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> rank;
				}

				if (Objects.size() == 0) {
					cout << "Немає об'єктів!\n";
					break;
				}
				cout << "Оберіть об'єкт:\n";

				choiceObject(Objects);

				int objectChoice;
				if (!choiceCheck(objectChoice)) {
					cout << "\nВведіть число!\n";
					continue;
				}
				if (objectChoice < 1 || objectChoice > Objects.size()) {
					cout << "Такого об'єкта немає!\n";
					break;
				}

				People.push_back(new Electrician(fullName, height, weight, gender, country, email, experience, rank, Objects[objectChoice - 1]));
				cout << "\nЕлектрика додано!\n";
			}
			break;
		}
		case 3: {
			if (People.size() == 0) {
				cout << "\nСписок людей порожній!\n";
				break;
			}
			cout << "\nКого видалити?\n";

			choicePerson(People);

			int personChoice;
			if (!choiceCheck(personChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}

			if (personChoice == 0)
				break;
			if (personChoice < 1 || personChoice > People.size()) {
				cout << "\nТакої людини немає!\n";
				break;
			}

			delete People[personChoice - 1];
			People.erase(
				People.begin() + personChoice - 1
			);
			cout << "\nЛюдину видалено!\n";
			break;
		}
		case 4: {
			string name;
			int reqExperience;
			int reqRank;

			cout << "\nВведіть назву об'єкта: ";
			cin.ignore();
			getline(cin, name);

			cout << "Введіть мінімальний стаж: ";
			cin >> reqExperience;
			while (cin.fail() || reqExperience < 0) {
				cout << "Невірний стаж! Введіть ще раз: ";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> reqExperience;
			}

			cout << "Введіть мінімальний розряд: ";
			cin >> reqRank;
			while (cin.fail() || reqRank < 0) {
				cout << "Невірний розряд! Введіть ще раз: ";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> reqRank;
			}

			Objects.push_back(new Object(reqExperience, reqRank, name));
			cout << "\nОб'єкт додано!\n";
			break;
		}
		case 5: {
			if (People.size() == 0) {
				cout << "\nСписок людей порожній!\n";
				break;
			}

			choicePerson(People);

			int personChoice;
			if (!choiceCheck(personChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}
			if (personChoice == 0)
				break;
			if (personChoice < 1 || personChoice > People.size()) {
				cout << "\nТакої людини немає!\n";
				break;
			}

			string newEmail;

			cout << "\nВведіть новий email: ";
			cin >> newEmail;

			People[personChoice - 1]->changeEmail(newEmail);

			cout << "\nEmail змінено!\n";
			break;
		}
		case 6: {
			if (People.size() == 0) {
				cout << "\nСписок людей порожній!\n";
				break;
			}
			cout << "\nОберіть робітника:\n";

			choicePerson(People);

			int personChoice;
			if (!choiceCheck(personChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}
			if (personChoice == 0)
				break;
			if (personChoice < 1 || personChoice > People.size()) {
				cout << "\nТакої людини немає!\n";
				break;
			}
			Worker* worker = dynamic_cast<Worker*>(People[personChoice - 1]);
			if (worker == nullptr) {
				cout << "\nЦя людина не є робітником!\n";
				break;
			}

			cout << "\n1.Збільшити оклад\n";
			cout << "2.Змінити посаду\n";
			cout << "0.Вихід\n";

			int workerChoice;
			if (!choiceCheck(workerChoice)) {
				cout << "Введіть число!\n";
				continue;
			}
			if (workerChoice == 1) {
				worker->increaseSalary();
				cout << "\nОклад збільшено!\n";
			}
			else if (workerChoice == 2) {
				string position;
				cout << "Введіть нову посаду: ";
				cin.ignore();
				getline(cin, position);

				worker->changePos(position);
				cout << "\nПосаду змінено!\n";
			}
			else if (workerChoice != 0) {
				cout << "\nНевірний вибір!\n";
			}
			break;
		}
		case 7: {
			if (People.size() == 0) {
				cout << "\nСписок людей порожній!\n";
				break;
			}
			cout << "\nОберіть електрика:\n";

			choicePerson(People);

			int personChoice;
			if (!choiceCheck(personChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}
			if (personChoice == 0)
				break;
			if (personChoice < 1 || personChoice > People.size()) {
				cout << "\nТакої людини немає!\n";
				break;
			}
			Electrician* electrician =dynamic_cast<Electrician*>(People[personChoice - 1]);

			if (electrician == nullptr) {
				cout << "\nЦя людина не є електриком!\n";
				break;
			}

			cout << "\n1.Перевірити допуск на поточний об'єкт\n";
			cout << "2.Змінити об'єкт\n";
			cout << "0.Вихід\n";

			int electricianChoice;
			if (!choiceCheck(electricianChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}
			if (electricianChoice == 1) {
				if (electrician->meetRequirements()) {
					cout << "\nЕлектрик допускається до роботи на об'єкті!\n";
				}
				else {
					cout << "\nЕлектрик НЕ допускається до роботи на об'єкті!\n";
				}
			}
			else if (electricianChoice == 2) {
				if (Objects.size() == 0) {
					cout << "\nНемає об'єктів!\n";
					break;
				}
				cout << "\nОберіть новий об'єкт:\n";

				choiceObject(Objects);

				int objectChoice;
				if (!choiceCheck(objectChoice)) {
					cout << "\nВведіть число!\n";
					continue;
				};
				if (objectChoice == 0)
					break;
				if (objectChoice < 1 || objectChoice > Objects.size()) {
					cout << "\nТакого об'єкта немає!\n";
					break;
				}

				electrician->changeObject(Objects[objectChoice - 1]);
				cout << "\nОб'єкт змінено!\n";
			}
			else if (electricianChoice != 0) {

				cout << "Невірний вибір!\n";
			}
			break;
		}
		case 8: {
			if (Objects.size() == 0) {
				cout << "\nНемає об'єктів!\n";
				break;
			}

			cout << "\nОберіть об'єкт:\n";

			choiceObject(Objects);

			int objectChoice;
			if (!choiceCheck(objectChoice)) {
				cout << "\nВведіть число!\n";
				continue;
			}
			if (objectChoice == 0)
				break;
			if (objectChoice < 1 || objectChoice > Objects.size()) {
				cout << "\nТакого об'єкта немає!\n";
				break;
			}

			bool found = false;

			cout << "\nЕлектрики, які можуть працювати на об'єкті:\n";
			for (int i = 0; i < People.size(); i++) {
				Electrician* electrician = dynamic_cast<Electrician*>(People[i]);
				if (electrician != nullptr) {
					if (electrician->meetRequirements(Objects[objectChoice - 1])) {
						People[i]->printName();
						cout << "\n";
						found = true;
					}
				}
			}
			if (found == false) {
				cout << "\nНемає електриків, які підходять!\n";
			}
			break;
		}
		case 0: {
			for (int i = 0; i < People.size(); i++) {
				delete People[i];
			}
			for (int i = 0; i < Objects.size(); i++) {
				delete Objects[i];
			}
			return 0;
		}
		default:
			cout << "\nТакого пункту меню немає!\n";
		}
	}
}