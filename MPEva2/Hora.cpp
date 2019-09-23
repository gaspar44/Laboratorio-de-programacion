#include "Hora.h"

Hora::Hora() {
	m_hora = 0;
	m_minutes = 0;
	m_seconds = 0;
	m_days = 0;
}

Hora::Hora(int hour,int minutes,int seconds) {
	m_hora = hour;
	m_minutes = minutes;
	m_seconds = seconds;
	m_days = 0;
}

Hora::Hora(const Hora &p) {
	m_hora = p.m_hora;
	m_minutes = p.m_minutes;
	m_seconds = p.m_seconds;
	m_days = p.m_days;
}

void Hora::setHora(int hour) {
	m_hora = hour;
}

void Hora::setMinuts(int minutes) {
	m_minutes = minutes;
}

void Hora::setSegons(int seconds) {
	m_seconds = seconds;
}

int Hora::getHora() {
	return m_hora;
}

int Hora::getMinuts(){
	return m_minutes;
}

int Hora::getSegons() {
	return m_seconds;
}

bool Hora::horaValida(){
	if (m_hora < 0 || m_minutes < 0 || m_seconds < 0)
		return false;

	else if (m_hora > 23 || m_seconds > 59 || m_minutes > 59)
		return false;

	return true;
}

Hora Hora::operator +(const int secondsToAdd) {
	Hora newHour = Hora(0,0,secondsToAdd);
	solveAddOperator(newHour);
	return This();

}

Hora Hora::operator +(const Hora &hora) {
	Hora newHour = Hora(hora);
	solveAddOperator(newHour);
	return This();
}

bool Hora::operator <(const Hora &hora) {
	if (m_hora < hora.m_hora)
		return true;

	else if (hora.m_hora < m_hora)
		return false;

	else if (m_minutes < hora.m_minutes)
		return true;

	else if (hora.m_minutes < m_minutes)
		return false;

	else if (m_seconds < hora.m_seconds)
		return true;

	else if (m_seconds < hora.m_seconds)
		return true;

	return false;

}

bool Hora::operator ==(const Hora &hora) {
	return (m_hora == hora.m_hora && m_minutes == hora.m_minutes && m_seconds == hora.m_seconds);
}

void Hora::solveAddOperator(Hora &hora) {
	int minuteCarry = addSeconds(hora.m_seconds);
	int hourCarry = addMinutes(minuteCarry,hora.m_minutes);
	addHours(hourCarry,hora.m_hora);
}


int Hora::addSeconds(int secondsToAdd){
	int minuteCarry = 0;
	m_seconds = m_seconds + secondsToAdd;

	if (m_seconds <= 59){
		return minuteCarry;
	}

	else if (m_seconds == 60){
		m_seconds = 0;
		minuteCarry = 1;
		return minuteCarry;
	}
	else {
		minuteCarry = m_seconds / 60;
		m_seconds = m_seconds % 60;
		return minuteCarry;
	}
}

int Hora::addMinutes(int minuteCarry,int minutesToAdd) {
	int hourCarry = 0;
	m_minutes = m_minutes + minutesToAdd + minuteCarry;

	if (m_minutes <= 59){
		return hourCarry;
	}

	else if (m_minutes == 60) {
		m_minutes = 0;
		hourCarry = 1;
		return hourCarry;
	}

	else {
		hourCarry = m_minutes / 60;
		m_minutes = m_minutes % 60;
		return hourCarry;
	}
}

void Hora::addHours(int hoursCarry,int hoursToAdd) {
	int dayCarry = 0;
	m_hora = m_hora + hoursCarry + hoursToAdd;

	if (m_hora == 24 ) {
		m_days = m_days + 1;
		m_hora = 0;
	}

	else {
		m_days = m_days + (m_hora / 24);
		m_hora = m_hora % 24;
	}

}

Hora Hora::This() const {
	return *this;
}
