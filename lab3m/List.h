#pragma once
#include <fstream>
#include "Iterator.h"
#include "CFile.h"

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
	~List();
	bool openFile(const char*);
	
	//methods
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
	void delLowCFile(string);
	void changeNameFile(string, string);

private:
	node_type *head;
	iterator *first, *last;
};

template <class T>
List<T>::List(){
    head = new node_type;
    first = last = NULL;
}

template <class T>
List<T>::~List(){
}

template <class T>
bool List<T>::openFile(const char *name){
    if(name == NULL) throw runtime_error("uncorrect filename (mark as NULL)");
    ifstream file;
    bool open = true;
    file.open(name, ifstream::in);
    if (file.is_open() == true){
        string str;
        if(is_class<T>::value == true){
            while(file >> str){
                CFile* obj = new CFile();
                obj->setAll(str);
                this->push_front(*obj);
            }
        }
    }
    else{
        open = false;
        throw runtime_error("file not exist");
    }
    file.close();
    return open;
}

template <class T>
void List<T>::push_front(const node_type val){
    if(last != NULL){
        node_type* new_node = new node_type(val);
        new_node->next = &*(*first);
        head = new_node;
        first = new iterator(new_node);
    }
    else{
        *head = val;
        head->next = NULL;
        first = new iterator(head);
        last = new iterator(head);
    }
}

template <class T>
void List<T>::pop_front(){
    if(last != NULL){
        head = &*(*first);
        (*first)++;
        delete head;
        head = &*(*first);
    }
    else throw runtime_error("list is empty");
}

template <class T>
bool List<T>::empty(){
    if(last == NULL) 
        return true;
    else 
        return false;
}

template <class T>
typename List<T>::iterator List<T>::begin(){
    return *first;
}

template <class T>
typename List<T>::iterator List<T>::end(){
    return *last;
}

template <class T>
typename List<T>::iterator List<T>::find(const node_type& val){
    if(last != NULL){
        node_type* node = new node_type(val);
        head = &*(*first);
        iterator* isFind = NULL;
        while(*first != NULL){
            if(node->data == (&*(*first))->data){
                isFind = new iterator(*first);
                first = new iterator(head);
                return *isFind;
            }
            (*first)++;
        }
    }
    else 
        return NULL;
}

template <class T>
void List<T>::clear(){
    if(last != NULL){
        int i = 0;
        while(*first != NULL){
            head = &*(*first);
            (*first)++;
            delete head;
        }
        first = NULL;
        last = NULL;
    }
    else 
        throw runtime_error("list is empty");
}

template <class T>
void List<T>::remove(const node_type val){
    if(last != NULL){
        head = &*(*first);
        node_type* node = new node_type(val);
        if(head->data == node->data){  
            node = head->next;
            delete head;
            head = node;
        }
        else{
            node_type* prTmp = new node_type(val);
            node = (&*(*first));
            (*first)++;
            while(*first != NULL){
                if((&*(*first))->data == prTmp->data){
                    node->next = (&*(*first))->next; 
                    delete &*(*first);
                    if(node->next == NULL)
                        last = new iterator(node);
                    break;
                }  
                node = (&*(*first));
                (*first)++;
            }
        }
        first = new iterator(head);
    }
    else throw runtime_error("empty list");
}

template <class T>
int List<T>::size(){
    int size = 0;
    if(last != NULL){
        head = &*(*first);
        while(*first != NULL){
            size++;
            (*first)++;
        }
        first = new iterator(head);
    }
    return size;
}

template <class T>
void List<T>::delLowCFile(string str){
    if(last != NULL){
        string tmp;
        tmp = str;
        tmp.resize(tmp.find_first_of('/'));
        str.erase(0, str.find_first_of('/') + 1);
        int day = atoi(tmp.c_str());
        tmp = str;
        tmp.resize(tmp.find_first_of('/'));
        str.erase(0, str.find_first_of('/') + 1);
        int month = atoi(tmp.c_str());
        int year = atoi(str.c_str());
        head = &*(*first);
        node_type* node = NULL;
        bool flag = false;
        while(*first != NULL){
            if(year > (&*(*first))->data.getYear())
                flag = true;
            else{
                if(year == (&*(*first))->data.getYear()){
                    if(month > (&*(*first))->data.getMonth())
                        flag = true;
                    else{
                        if(month == (&*(*first))->data.getMonth()){
                            if(day > (&*(*first))->data.getDay()) flag = true;
                            else flag = false;
                        }
                        else flag = false;
                    }
                }
                else flag = false;
            }
            if(flag == true){
                if(node == NULL) {
                    head = head->next;
                    node = &*(*first);
                    (*first)++;
                    delete node;
                    node = NULL;
                    continue;
                }
                else{
                    node->next = (&*(*first))->next; 
                    delete &*(*first);
                    first = new iterator(node->next);
                    if(node->next == NULL)
                        last = new iterator(node);
                }
            }
            node = &*(*first);
            (*first)++;
        }
        first = new iterator(head);
    }
}

template <class T>
void List<T>::changeNameFile(string lastName, string newName){
    if(first != NULL){
        if(is_class<T>::value == true){
            head = &*(*first);
            while(*first != NULL){
                if(strcmp((&*(*first))->data.getFilename(), lastName.c_str()) == 0){
                    (&*(*first))->data.setFilename(newName.c_str());
                    break;
                }
                (*first)++;
            }
            first = new iterator(head);
        }
    }
}

template <class T>
void List<T>::splice(iterator _Where, List<T>& _Right){
    if(last != NULL){
        head = &*(*first);
        node_type* node;
        if(head == &*_Where){
            node = head->next;
            _Right.push_front(*_Where);
            delete head;
            head = node;
        }
        else{
            (*first)++;
            while(*first != NULL){
                if(*first == &*_Where){
                    node->next = (&*(*first))->next; 
                    _Right.push_front(*_Where);
                    delete &*(*first);
                    if(node->next == NULL)
                        last = new iterator(node);
                    break;
                }
                node = &*(*first);
                (*first)++;
            }
        }
        first = new iterator(head);
    }
    else throw logic_error("empty list");
}

template <class T>
void List<T>::Print(){
    if(last != NULL){
        cout << "---\nFileName\tCreationData\tSize\n\n";
        head = &*(*first);
        while(*first != NULL){
            (&*(*first))->Print();
            (*first)++;
        }
        first = new iterator(head);
    }
}
