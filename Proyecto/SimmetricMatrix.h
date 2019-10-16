#pragma once


class SimmetricMatrix
{
public:
	SimmetricMatrix() : m_matriu(nullptr), m_nFiles(0), m_nColumnes(0) {}
	SimmetricMatrix(int nFiles, int nColumnes) : m_matriu(nullptr), m_nFiles(0), m_nColumnes(0) { resize(nFiles, nColumnes); }
	SimmetricMatrix(const SimmetricMatrix& m) : m_matriu(nullptr), m_nFiles(0), m_nColumnes(0) { *this = m; }
	~SimmetricMatrix();

	void resize(int nFiles, int nColumnes);
	SimmetricMatrix& operator=(const SimmetricMatrix& m);
	void setValor(int fila, int columna, float valor);
	bool getValor(int fila,int columna,float &valor) const ;

	bool esBuida() const { return (m_matriu == nullptr); }
	int getNFiles() const { return m_nFiles; }
	int getNColumnes() const { return m_nColumnes; }

protected:
	float **m_matriu;
	int m_nFiles;
	int m_nColumnes;
	void initializeEmptyMatrix(float** matrix,int nFiles,int nColumnes);
	void setValor(float** matrix,int row, int column, float value);
	void releaseMatrixMemory();
	void fillNewMatrixWithOld(float **sourceMatrix,float **destinyMatrix, int rowLimiter,int columnLimiter);
};
