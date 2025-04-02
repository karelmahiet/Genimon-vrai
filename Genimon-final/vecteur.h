#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>
using namespace std;

template <typename T>
class Vecteur
{
public:
	Vecteur();
	~Vecteur();

	int Capacite();
	int Taille();

	void doublerCapacite();
	void vider();

	bool estVide();

	bool ajouterElement(T nouveauElement);
	void retirerElement(int index);

	T getElement(int index);

	T operator[](int index);
	void operator+=(T donnee);

private:
	int capacite;
	int taille;
	T* listeElements;
};

template <typename T>
Vecteur<T>::Vecteur()
{
	capacite = 1;
	taille = 0;
	listeElements = new T[capacite];
}

template <typename T>
Vecteur<T>::~Vecteur()
{
	vider();
	delete[] listeElements;
}

template <typename T>
int Vecteur<T>::Capacite()
{
	return capacite;
}

template <typename T>
int Vecteur<T>::Taille()
{
	return taille;
}

template <typename T>
void Vecteur<T>::doublerCapacite()
{
	capacite *= 2;
	T* listeElements2 = new T[capacite];
	for (int i = 0; i < taille; i++) //copie des informations
	{
		listeElements2[i] = listeElements[i];
	}
	delete[] listeElements;
	listeElements = listeElements2;
}

template <typename T>
void Vecteur<T>::vider()
{
	for (int i = taille - 1; i >= 0; i--)
	{
		retirerElement(i);
	}

	taille = 0;
}

template <typename T>
bool Vecteur<T>::estVide()
{
	return taille == 0;
}

template <typename T>
bool Vecteur<T>::ajouterElement(T nouveauElement)
{
	if (taille >= capacite)
	{
		doublerCapacite();
	}

	listeElements[taille] = nouveauElement;
	taille++;

	return true;
}

template <typename T>
void Vecteur<T>::retirerElement(int index)
{
	if (index < taille)
	{
		delete listeElements[index];
		if (index + 1 < capacite) //Ne décale pas si on retire à la fin
		{
			for (int i = index + 1; i < capacite; i++) //décale les éléments
			{
				listeElements[i - 1] = listeElements[i];
			}
		}

		taille--;
	}
}

template <typename T>
T Vecteur<T>::getElement(int index)
{
	T element = NULL;
	if (index < taille)
	{
		element = listeElements[index];
	}

	return element;
}

//---------- Surcharge d'opérateurs ----------

template <typename T>
T Vecteur<T>::operator[](int index)
{
	return getElement(index);
}

template <typename T>
void Vecteur<T>::operator+=(T donnee)
{
	ajouterElement(&donnee);
}

#endif
