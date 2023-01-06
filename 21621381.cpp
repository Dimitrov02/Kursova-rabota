#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Film
{
private:

	string name;
	string channel;
	int startHour;
	int endHour;

public:


	Film() {}//default constructor

	Film(string name, string channel, int startHour, int endHour)//explicit constructor
	{
		this->name = name;
		this->channel = channel;
		this->startHour = startHour;
		this->endHour = endHour;
	}
	void setName(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return name;
	}
	void setChannel(string channel)
	{
		this->channel = channel;
	}
	string getChannel()
	{
		return channel;
	}
	void setStartHour(int startHour)
	{
		this->startHour = startHour;
	}
	int getStartHour()
	{
		return startHour;
	}
	void setEndHour(int endHour)
	{
		this->endHour = endHour;
	}
	int getEndHour()
	{
		return endHour;
	}
	bool operator==(const Film& other) const {
		return name == other.name && channel == other.channel
			&& startHour == other.startHour && endHour == other.endHour;
	}
	bool operator<(const Film& other) const {
		return startHour < other.startHour;
	}
	bool overlaps(const Film& other) const {
		return (startHour >= other.startHour && startHour <= other.endHour)
			|| (endHour >= other.startHour && endHour <= other.endHour)
			|| (startHour <= other.startHour && endHour >= other.endHour);
	}
	string toString() const {
		return name + " (" + channel + ") [" + to_string(startHour) + "-" + to_string(endHour) + "]";
	}
	friend ostream& operator<<(ostream& os, const Film& film)
	{
		os << film.toString();
		return os;
	}
	friend istream& operator>>(istream& is, Film& film)
	{
		is >> film.name >> film.channel >> film.startHour >> film.endHour;
		return is;
	}
};

class Favourites
{
private:

	vector<Film> m_listFilms;

public:

	Favourites() {}

	// Explicit constructor
	Favourites(vector<Film> listFilms) : m_listFilms(listFilms) {}

	// Function to add a film to the list
	void addFilm(const Film& film)
	{
		m_listFilms.push_back(film);
	}

	void removeFilm(const string& name) {
		for (vector<Film>::iterator it = m_listFilms.begin(); it != m_listFilms.end(); it++) {
			if (it->name == name) {
				m_listFilms.erase(it);
				break;
			}
		}
	}

	string toString() const {
		string str = "";
		for (unsigned int i = 0; i < m_listFilms.size(); i++) {
			str += m_listFilms[i].toString();
			if (i < m_listFilms.size() - 1) {
				str += ", ";
			}
		}
		return str;
	}
	static Favourites filmsWithoutOverlap(const Favourites& fav1, const Favourites& fav2) {
		vector<Film> listFilms;
		for (unsigned int i = 0; i < fav1.m_listFilms.size(); i++) {
			bool overlaps = false;
			for (unsigned int j = 0; j < fav2.m_listFilms.size(); j++) {
				if (fav1.m_listFilms[i].overlaps(fav2.m_listFilms[j])) {
					overlaps = true;
					break;
				}
			}
			if (!overlaps) {
				listFilms.push_back(fav1.m_listFilms[i]);
			}
		}
		for (unsigned int i = 0; i < fav2.m_listFilms.size(); i++) {
			bool overlaps = false;
			for (unsigned int j = 0; j < fav1.m_listFilms.size(); j++) {
				if (fav2.m_listFilms[i].overlaps(fav1.m_listFilms[j])) {
					overlaps = true;
					break;
				}
			}
			if (!overlaps) {
				listFilms.push_back(fav2.m_listFilms[i]);
			}
		}
		return Favourites(listFilms);
	}
};

int main() 
{
	Favourites fav1, fav2;

	cout << "Favourites 1: " << fav1.toString() << endl;
	cout << "Favourites 2: " << fav2.toString() << endl;

	fav1.addFilm(Film("The Shawshank Redemption", "HBO", 9, 11));
	fav1.addFilm(Film("The Godfather", "Cinemax", 20, 23));

	fav2.addFilm(Film("Forrest Gump", "HBO", 10, 12));
	fav2.addFilm(Film("The Godfather: Part II", "Cinemax", 19, 22));

	cout << "Favourites 1: " << fav1.toString() << endl;
	cout << "Favourites 2: " << fav2.toString() << endl;

	fav1.removeFilm("The Shawshank Redemption");

	cout << "Favourites 1: " << fav1.toString() << endl;

	Favourites fav3 = Favourites::filmsWithoutOverlap(fav1, fav2);

	cout << "Favourites 3: " << fav3.toString() << endl;

	return 0;
}
