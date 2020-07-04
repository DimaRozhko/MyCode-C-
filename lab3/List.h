/*******************************************
*file: List.h
*last modified: 01.05.2020
*********************************************/
#pragma once
#include "Iterator.h"
#include "Bus.h"
#include <fstream>

using namespace std;
template <class T>
class List{
	
	struct ListNode{
		T data;
		ListNode * next;
		ListNode(){
			next = NULL;
		}
		ListNode( T dat ){
			data = dat;
		}
		void Print(){
			cout<<data;
		}
	};
	
public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
    List(int parkNum, bool inPark);
	~List();
	
	//methods
    bool load(const char *filename);
	iterator begin();//Returns an iterator addressing the first element 
	iterator end();//Returns an iterator that addresses the location 
   //succeeding the last element
	

	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.

	iterator find(const node_type & val);//Returns an iterator to the 
// first element in a list that 
//match a specified value.

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front( const node_type val);//Adds an element to the beginning 
  //of a list.
	void remove(const node_type val);//Erases first element in a list that 
   //match a specified value.
		

	int size();//Returns the number of elements in a list.

	void splice( iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
	void	Print();//Dumps list into the screen
    void PrintFindBus(const char* route_num);
    void changeNameByNumBus(const char* bus_num, const char* newDriver);
    int getParkNum(){return busParkNum;}
private:
	node_type *head;
	iterator *first, *last;
    int busParkNum;
    bool isInPark;
};

template <class T>
List<T>::List(){
    head = new node_type;
    first = last = NULL;
    busParkNum = 0;
    isInPark = true;
}

template <class T>
List<T>::List(int parkNum, bool inPark){
    head = new node_type;
    first = last = NULL;
    busParkNum = parkNum;
    isInPark = inPark;
}

template <class T>
List<T>::~List(){
}

template <class T>
bool List<T>::load(const char *filename){
    if(filename == NULL) throw runtime_error("ERROR: NULL in name of file");
    ifstream fl;
    string strTmp;
    fl.open(filename, ifstream::in);
    bool cond = true;
    if (fl.is_open() == false){
        cond = false;
        throw runtime_error("ERROR: file not exist");
    }
    else{
        string strTmp;
        if(is_same<T, Bus>::value == true){
            while(fl >> strTmp){
                Bus* objNode = new Bus();
                objNode->setAllFields(strTmp);
                this->push_front(*objNode);
            }
        }
    }
    fl.close();
    return cond;
}

template <class T>
void List<T>::push_front(const node_type val){
    if(first == NULL){
        *head = val;
        head->next = NULL;
        first = new iterator(head);
        last = new iterator(head);
    }else{
        node_type* new_node = new node_type(val);
        new_node->next = &*(*first);
        head = new_node;
        delete first;
        first = new iterator(new_node);
    }
}

template <class T>
typename List<T>::iterator List<T>::begin(){
    if(first == NULL) throw runtime_error("ERROR: NULL in pointer 'first'");
    else return *first;
}

template <class T>
typename List<T>::iterator List<T>::end(){
    if(last == NULL) throw runtime_error("ERROR: NULL in pointer 'last'");
    else return *last;
}

template <class T>
void List<T>::clear(){
    if(first != NULL){
        iterator* tmp = NULL;
        while(*first != NULL){
            tmp = first;
            head = &*(*first);
            (*first)++;
            delete head;
            delete tmp;
        }
        first = last = NULL;
    }
    else throw logic_error("ERROR: can't clear (empty list)");
}

template <class T>
bool List<T>::empty(){
    if(first == NULL && last == NULL) return true;
    else return false;
}

template <class T>
typename List<T>::iterator List<T>::find(const node_type& val){
    iterator* tmp = NULL;
    if(first != NULL){
        node_type* nodeTmp = new node_type(val);
        head = &*(*first);
        while(*first != NULL){
            if(nodeTmp->data == (&*(*first))->data){
                tmp = new iterator(*first);
                break;
            }
            (*first)++;
        }
        delete first;
        first = new iterator(head);
    }
    if(tmp == NULL) return NULL;
    else return *tmp;
}

template <class T>
void List<T>::pop_front(){
    if(first != NULL){
        head = &*(*first);
        (*first)++;
        delete head;
        head = &*(*first);
    }
    else throw logic_error("ERROR: can't pop front (empty list)");
}

template <class T>
void List<T>::remove(const node_type val){
    if(first != NULL){
        head = &*(*first);
        node_type* prNode = new node_type(val);
        if(head->data == prNode->data){  
            prNode = head->next;
            delete head;
            head = prNode;
        }
        else{
            node_type* prTmp = new node_type(val);
            prNode = (&*(*first));
            (*first)++;
            while(*first != NULL){
                if((&*(*first))->data == prTmp->data){
                    prNode->next = (&*(*first))->next; 
                    delete &*(*first);
                    if(prNode->next == NULL)
                        last = new iterator(prNode);
                    break;
                }  
                prNode = (&*(*first));
                (*first)++;
            }
        }
        delete first;
        first = new iterator(head);
    }
    else throw logic_error("ERROR: can't remove node (empty list)");
}

template <class T>
int List<T>::size(){
    int size = 0;
    if(first != NULL){
        head = &*(*first);
        while(*first != NULL){
            (*first)++;
            size++;
        }
        delete first;
        first = new iterator(head);
    }
    return size;
}

template <class T>
void List<T>::splice(iterator _Where, List<T>& _Right){
    if(first != NULL){
        if(this->getParkNum() == _Right.getParkNum()){
            head = &*(*first);
            node_type* prNode;
            if(head == &*_Where){
                prNode = head->next;
                _Right.push_front(*_Where);
                delete head;
                head = prNode;
            }
            else{
                (*first)++;
                while(*first != NULL){
                    if(*first == &*_Where){
                        prNode->next = (&*(*first))->next; 
                        _Right.push_front(*_Where);
                        delete &*(*first);
                        if(prNode->next == NULL)
                            last = new iterator(prNode);
                        break;
                    }
                    prNode = &*(*first);
                    (*first)++;
                }
            }
            delete first;
            first = new iterator(head);
        }
        else throw logic_error("ERROR: uncorrect number park and bus on way");
    }
    else throw logic_error("ERROR: can't remove node (empty list)");
}



template <class T>
void List<T>::Print(){
    if(first != NULL){
        cout << "-------------------------------------------\n";
        cout << ">Output list bus in <PARK-" << busParkNum << ">\n Condition: ";
        if(isInPark == true) cout << "STAY\n";
        else cout << "IN WAY\n";
        cout << "\t|NumBus\t|Driver\t|NumRoute\n";
        cout << "\t-\t-\t-\n";
        head = &*(*first);
        while(*first != NULL){
            (&*(*first))->Print();
            (*first)++;
        }
        delete first;
        first = new iterator(head);
        cout << this->size() << " list nodes" << endl;
        cout << "-------------------------------------------\n";
    }
}

template <class T>
void List<T>::PrintFindBus(const char* route_num){
    if(first != NULL){
        if(is_same<T, Bus>::value == true){
            cout << "___________________________________________\n\n";
            cout << ">Output list bus in <PARK-" << busParkNum << ">\n";
            cout << " Find node by route number - \"" << route_num << "\"\n";
            cout << "\t|NumBus\t|Driver\t|NumRoute\n";
            cout << "\t-\t-\t-\n";
            head = &*(*first);
            int i = 0;
            while(*first != NULL){
                if(strcmp((&*(*first))->data.GetRouteNum(), route_num) == 0){
                    (&*(*first))->Print();
                    i++;
                }
                (*first)++;
            }
            delete first;
            first = new iterator(head);
            cout << i << " buses found on this route\n";
            cout << "___________________________________________\n";
        }
    }
    else cout << "WARNING: empty list\n";
}

template <class T>
void List<T>::changeNameByNumBus(const char* bus_num, const char* newDriver){
    if(first != NULL){
        if(is_same<T, Bus>::value == true){
            head = &*(*first);
            while(*first != NULL){
                if(strcmp((&*(*first))->data.GetBusNum(), bus_num) == 0){
                    (&*(*first))->data.setDriver(newDriver);
                    break;
                }
                (*first)++;
            }
            delete first;
            first = new iterator(head);
        }
    }
    else cout << "WARNING: empty list\n";
}
