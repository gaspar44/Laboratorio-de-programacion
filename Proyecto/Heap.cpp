#include "Heap.h"

Heap::Heap(const Heap& h)
{//constructor de copia
	m_data = h.m_data;
	m_maxElement = h.m_maxElement;
	m_actualPosition = h.m_actualPosition;
	m_index = h.m_index;
}

void Heap::clear()
{
	m_data.clear();
	m_index.clear();
	m_maxElement=0;
	m_actualPosition=-1;
}

Heap& Heap::operator=(const Heap& h)
{
	if (this != &h)
	{
		m_data = h.m_data;
		m_maxElement = h.m_maxElement;
		m_actualPosition = h.m_actualPosition;
		m_index = h.m_index;
	}
	return *this;
}

bool Heap::operator==(const Heap& h)
{
	bool iguals = true;
	if (m_actualPosition != h.m_actualPosition)
	{
		iguals = false;
	}
	else
	{

		int i = 0;
		while ((i <= m_actualPosition) && iguals)
		{
			if (!(m_data[i] == h.m_data[i]))
			{
				iguals = false;
				cout << "MDATA DIFERENT A POS: " << i << endl;
			}
			i++;
		}
	}
	return iguals;
}

std::ostream& operator<<(std::ostream& out, const Heap& h)
{
	if (h.m_actualPosition == -1) { out << "|---->BUIT" << endl; }
	else	h.printRec(out, 0, 0);
	return out;
}

void Heap::delElem(int pos1)
{
	int pos = m_index[pos1];
	if ((pos >= 0) && (pos <= m_actualPosition))
	{
		//Posar element ultim a pos i decrementar nombre elements

		//Modifiquem que ara element que estava a pos esta a 0
		m_index[m_data[pos].getPos().first] = 0;
		m_index[m_data[0].getPos().first] = -1;

		//Posar element ultim a pos i decrementar nombre elements
		swapPosition(0, pos);
		m_actualPosition--;
		descend(pos);
	}
}

void Heap::modifElem(const ElemHeap& novaData)
{
	if (novaData.getVal() == -2 || novaData.getVal() == 0){
//		cout<<"FUCKKKKKKK"<<endl;
//		cout<<"pos: "<<novaData.getPos().first<<","<<novaData.getPos().second<<endl;
//		cout<<"valor: "<<novaData.getVal()<<endl;
		return;
	}


	int pos = m_index[novaData.getPos().first];
	if ((pos >= 0) && (pos <= m_actualPosition))
	{
		//Modifiquem element
		if (m_data[pos] > novaData)
		{
			m_data[pos] = novaData;
			descend(pos);
		}
		else
			if (m_data[pos] < novaData)
			{
				m_data[pos] = novaData;
				ascend(pos);
			}
			else
			{
				m_data[pos] = novaData;
			}
	}
}

void Heap::insert(const ElemHeap& el)
{
	if ((m_actualPosition + 1) < m_maxElement) //Si hi ha espai
	{//inserim element al final
		m_actualPosition++;
		m_data[m_actualPosition] = el;
		//Indiquem que element el esta posicio m_act
		m_index[el.getPos().first] = m_actualPosition;

		int posAct = m_actualPosition;
		// Fix the max heap property if it is violated
		while (posAct != 0 && m_data[posAct] >= m_data[getFather(posAct)])
		{
			//Indiquem que element que estava a posAct estara a pare(posAct) i viceversa
			int indexAux = m_index[m_data[posAct].getPos().first];
			m_index[m_data[posAct].getPos().first] = m_index[m_data[getFather(posAct)].getPos().first];
			m_index[m_data[getFather(posAct)].getPos().first] = indexAux;

			swapPosition(posAct, getFather(posAct));

			posAct = getFather(posAct);
		}
	}
}

void Heap::delMax()
{
	if (m_actualPosition >= 0)
	{
		//Modifiquem que ara element que estava a m_act estara a 0
		m_index[m_data[m_actualPosition].getPos().first] = 0;
		m_index[m_data[0].getPos().first] = -1;
		//Posar element ultim a l'arrel i decrementar nombre elements
		swapPosition(0, m_actualPosition);

		m_actualPosition--;
		descend(0);
	}
}

void Heap::descend(int posAct)
{
	int fEsq = getLeftSon(posAct);
	int fDret = getRightSon(posAct);
	int mesGran = posAct;
	if (fEsq <= m_actualPosition && m_data[fEsq] > m_data[posAct])
		mesGran = fEsq;
	if (fDret <= m_actualPosition && m_data[fDret] > m_data[mesGran])
		mesGran = fDret;
	if (mesGran != posAct)
	{
		//Modifiquem que ara element que estava a m_act estara a 0
		int indAux = m_index[m_data[posAct].getPos().first];
		m_index[m_data[posAct].getPos().first] = m_index[m_data[mesGran].getPos().first];
		m_index[m_data[mesGran].getPos().first] = indAux;

		swapPosition(posAct, mesGran);
		descend(mesGran);
	}
}

void Heap::ascend(int posAct)
{
	int fPare = getFather(posAct);
	if (fPare >= 0 && m_data[fPare] < m_data[posAct])
	{
		//Indiquem que element que estava a posAct estara a pare(posAct) i viceversa
		int indexAux = m_index[m_data[posAct].getPos().first];
		m_index[m_data[posAct].getPos().first] = m_index[m_data[fPare].getPos().first];
		m_index[m_data[fPare].getPos().first] = indexAux;

		swapPosition(posAct, fPare);
		ascend(fPare);
	}
}

/////////////////////////////////////////////////////////////////////////////
// print():                                                                //
//         Metode public presenta Heap per pantalla                        //
// readRec(int pos, int n)                                                 //
//         Metode privat que escriu HEap per pantalla de forma recursiva   //
// |--arrel                                                                //
// |---->FillDret1                                                         //
// |------>FillDret2                                                       //
// |------>FillEsquerre2                                                   //
// |---->FillEsquerre1                                                     //
/////////////////////////////////////////////////////////////////////////////

std::ostream& Heap::printRec(std::ostream& out, int pos, int n) const
{
	if (pos <= m_actualPosition)
	{//Pintem arbre
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "|-->" << m_data[pos] << endl;
		if (((2 * pos) + 1) <= m_maxElement)
		{//printem subarbre esquerre
			printRec(out, getLeftSon(pos), n + 1);
		}
		if ((2 * pos) < m_maxElement)
		{//printem subarbre dret
			printRec(out, getRightSon(pos), n + 1);
		}
	}
	return out;
}
