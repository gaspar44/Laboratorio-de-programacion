#pragma once


class Matriu
{
public:
	Matriu() : m_matriu(nullptr), m_nFiles(0), m_nColumnes(0) {}
	Matriu(int nFiles, int nColumnes) : m_matriu(nullptr), m_nFiles(0), m_nColumnes(0) { resize(nFiles, nColumnes); }
	Matriu(const Matriu& m); //: m_matriu(nullptr), m_nFiles(0), m_nColumnes(0) { *this = m; }
	~Matriu();

	void resize(int nFiles, int nColumnes);
	void transpose();
	Matriu& operator=(const Matriu& m);
	void setValor(int fila, int columna, float valor);
	float getValor(int fila,int columna) const ;
	Matriu operator+(const Matriu& m);
	Matriu operator+(float s);
	bool operator==(const Matriu& m);

	bool esBuida() const { return (m_matriu == nullptr); }
	int getNFiles() const { return m_nFiles; }
	int getNColumnes() const { return m_nColumnes; }
private:
	float **m_matriu;
	int m_nFiles;
	int m_nColumnes;
	void initializeEmptyMatrix(float** matrix,int nFiles,int nColumnes);
	void releaseMatrixMemory();
	bool haveReleasedBefore = false;
};
