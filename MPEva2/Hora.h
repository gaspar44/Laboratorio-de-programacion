#pragma once

class Hora {
	public:
		Hora();
		Hora(int hour,int minute,int seconds);
		Hora(const Hora &p);
		void setHora(int hora);
		void setMinuts(int minutes);
		void setSegons(int seconds);
		int getHora();
		int getMinuts();
		int getSegons();
		bool horaValida();
		Hora operator+ (const Hora &hora);
		Hora operator+ (const int seondsToAdd);
		bool operator< (const Hora &hora);
		bool operator==(const Hora &hora) ;

	private:
		int m_hora;
		int m_minutes;
		int m_seconds;
		int m_days;
		void solveAddOperator(Hora &hora);
		int addSeconds(int secondsToAdd);
		int addMinutes(int minuteCarry,int minutesToAdd);
		void addHours(int hoursCarry,int hoursToAdd);
		Hora This() const;
};
