#define _CRT_SECURE_NO_WARNINGS
#include "BinTree.h"
#include <typeinfo>
#define LEN 100
// #define DEBUG

template<class T>
BinTree<T>::BinTree() {
    root = NULL;
   //if (typeid(T).hash_code() != typeid(CTreeNode).hash_code()){
    if(strcmp(typeid(T).name(), "9CTreeNode") != 0){
#ifdef DEBUG
        printf("\nUNCORRECT TYPE\n");
#endif // !DEBUG
        checkPinter(root, this);
    }
    data = NULL;
    cur = NULL;
    pre = NULL;
    flPtr = NULL;
    SizeMemON = 0;
    NumElemTree = 0;
}

template<class T>
BinTree<T>::~BinTree() {
    for (int i = 0; i < countOut; i++){
        delete[] data[i];
    }
    delete[] data;
    countOut = 0;
    delete root;
    delete cur;
}

template<class T>
int BinTree<T>::GetCount() {
    return countOut;
}

template<class T1, class T2>
void checkPinter(T1* ptr1, T2* ptr2) {
    if (ptr1 == NULL) {
#ifdef DEBUG
        printf("\nCHECK FAULT\n");
#endif // DEBUG
        delete ptr2;
        exit(404);
    }
}

template<class T>
void BinTree<T>::openFile(const char* file, const char* use) {
    checkPinter(file, this);
    checkPinter(use, this);
    //strcpy(namef, file);
    //strcpy(namec, use);
    flPtr = fopen(file, use);
    if (flPtr == NULL) {
#ifdef DEBUG
        printf("ERROR: INCORRECT OPEN FILE\n");
#endif // DEBUG
        exit(404);								//exit the program code 404 
    }
    bool flag = true;
    count = 0;
    char elem;
    while (fread(&elem, sizeof(char), 1, flPtr)) {
        if (elem == '\n') {
            if (flag == true) {
                count++;
            }
            flag = false;
        }
        else {
            flag = true;
        }
    }
    fseek(flPtr, -1, SEEK_CUR);
    fread(&elem, sizeof(char), 1, flPtr);
    if (elem != '\n')
        count++;
    fclose(flPtr);
    flPtr = fopen(file, use);
    data = new char* [count];
    for (int i = 0; i < count; i++){
        data[i] = new char[LEN];
    }
    int j = 0;
    count = 0;
    while (fread(&elem, sizeof(char), 1, flPtr)) {
        if (elem == '\n') {
            data[count][j] = '\0';
            count++;
            j = 0;
        }
        else {
            if (j < LEN) {
                data[count][j] = elem;
            }
            j++;
        }
    }
    fseek(flPtr, -1, SEEK_CUR);
    fread(&elem, sizeof(char), 1, flPtr);
    if (elem != '\n') {
        data[count][j] = '\0';
        count++;
    }
    countOut = count;
    count = 0;
    fclose(flPtr);
}

template<class T>
int BinTree<T>::comparisonStr(const char* str1, const char* str2) {
    int i = 0, flag = 0;
    condition = false;
    lenStr = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] == str2[i]) {
            condition = true;
            lenStr++;
            i++;
        }
        else {
            if (str1[i] > str2[i])
                flag++;
            else
                flag--;
            break;
        }
    }
    return flag;
}

template<class T>
void* BinTree<T>::SearchNode(Node* dat, char* str1) {
    char* str2 = (char*)dat->value->GetField(3);
    if (dat->left != NULL && dat->right != NULL) {
        if (comparisonStr(str1, str2) == 1) {
            return SearchNode(dat->right, str1);
        }
        else {
            return SearchNode(dat->left, str1);
        }
    }
    else {
        char* str3 = str2;
        if (dat->left != NULL) {
            str3 = (char*)dat->left->value->GetField(3);
            comparisonStr(str1, str3);
            if (condition == true)
                return SearchNode(dat->left, str3);
        }
        else {
            if (dat->right != NULL) {
                str3 = (char*)dat->right->value->GetField(3);
                comparisonStr(str1, str3);
                if (condition == true)
                    return SearchNode(dat->right, str3);
            }
        }
        if (comparisonStr(str1, str2) == 1) {
            condition = true;
        }
        else {
            condition = false;
        }
        return dat;
    }
    return NULL;
}

template<class T>
void BinTree<T>::PrintRec(Node* PrintNode) {
    if (PrintNode != NULL) {
        printf("\n+-------Node: %p------------", PrintNode);
        printf("\n+\tLeft: %p", PrintNode->left);
        printf("\n+\tRight: %p", PrintNode->right);
        PrintNode->value->PrintObj();
        if (PrintNode->left != NULL) {
            PrintRec(PrintNode->left);
        }
        if (PrintNode->right != NULL) {
            PrintRec(PrintNode->right);
        }
    }
}

template<class T>
void BinTree<T>::PrintAll() {
    Node* Go = root;
    printf("\nStart print tree");
    PrintRec(Go);
    printf("\nEnd print tree\n");
}

template<class T>
void BinTree<T>::AddNode(char* str) {
    condition = false;
    Node* rootTmp = root;
    Node* curTmp = (Node*)SearchNode(root, str);
    if (condition == true) {
        curTmp->right = cur;
    }
    else {
        curTmp->left = cur;
    }
    root = rootTmp;
}

template<class T>
void BinTree<T>::addItem() {
    cur = new Node;
    cur->left = NULL;
    cur->right = NULL;  
    cur->value = new T;
    SizeMemON = strlen(data[count]);
    char* str = new char[LEN];
    strcpy(str, data[count]);
    if (count < countOut) {
        char* strCheck = cur->value->SetValueObj(str, SizeMemON);//->SetValue(cur->value, str, SizeMemON);
        if (root == NULL) {
            root = cur;
        }
        else {
            AddNode(strCheck);
        }
        delete[] strCheck;
    }
    count++;
    delete[] str;
}

template<class T>
void BinTree<T>::addApp(const char* str) {
    checkPinter(str, this);
    cur = new Node;
    cur->value = new T;
    cur->left = NULL;
    cur->right = NULL;
    char* strCheck = cur->value->SetValueObj(str, strlen(str));
    AddNode(strCheck);
    delete[] strCheck;
}

template<class T>
void* BinTree<T>::removeRec(Node* dat, const char* str) {
    if (NumElemTree > 2) {

        if ((comparisonStr((const char*)dat->value->GetField(NumElemTree), str) == 0) && (lenStr == (int)strlen(str))) {
            condition = true;
            return dat;
        }

    }
    else {
        for (int i = 0; i < 4; i++) {
            if (*(int*)dat->value->GetField(NumElemTree) == atoi(str)) {
                condition = true;
                return dat;
            }
        }
    }
    condition = false;
    if (dat->left != NULL) {
        cur = (Node*)removeRec(dat->left, str);
        if ((cur != NULL) && (condition == true)) {
            pre = dat;
            condition = false;
        }
    }
    if (dat->right != NULL) {
        cur = (Node*)removeRec(dat->right, str);
        if ((cur != NULL) && (condition == true)) {
            pre = dat;
            condition = false;
        }
    }
    return cur;
}

template<class T>
void BinTree<T>::removeNode(const char* str) {
    checkPinter(str, this);
    lenStr = 0;
    cur = NULL;
    Node* del = NULL;
    int count = 4;
    NumElemTree = 0;
    SizeMemON = 0;
    char** dataTab = new char* [4];
    for (int i = 0; i < count; i++) {
        dataTab[i] = new char[100];
    }
    while (str[0] != '\0') {
        if (str[0] == ';') {
            strncpy(dataTab[SizeMemON], str - NumElemTree, NumElemTree);
            dataTab[SizeMemON][NumElemTree] = '\0';
            SizeMemON++;
            NumElemTree = 0;
        }
        else {
            NumElemTree++;
        }
        lenStr++;
        str++;
    }
    if (SizeMemON != 0) {
        strncpy(dataTab[SizeMemON], str - NumElemTree, NumElemTree);
        NumElemTree = 4;
        del = (Node*)removeRec(root, dataTab[0]);
        if (del != NULL) {
            NumElemTree = 3;
            condition = false;
            if ((comparisonStr((const char*)del->value->GetField(NumElemTree), dataTab[2]) == 0) && (lenStr == (int)strlen(dataTab[2]))) {
                NumElemTree = 1;
                if (*(int*)del->value->GetField(NumElemTree) == atoi(dataTab[1])) {
                    if (*(int*)del->value->GetField(NumElemTree) == atoi(dataTab[3])) {
                        if (*(int*)del->value->GetField(NumElemTree) == atoi(dataTab[3] + 2)) {
                            if (*(int*)del->value->GetField(NumElemTree) == atoi(dataTab[3] + 5)) {
                                condition = true;
                            }
                        }
                    }
                }
            }
            if (condition == false)
                del = NULL;
        }
    }
    else {
        #ifdef DEBUG
        printf("\nUNCORRECT INPUT STRING\n");
        #endif // DEBUG
        str = NULL;
        checkPinter(str, this);
        // str -= lenStr;
        // if (atoi(str) == 0) {
        //     NumElemTree = 3;
        //     count = 5;
        // }
        // else {
        //     NumElemTree = 1;
        //     count = 2;
        // }
        // while ((NumElemTree < count) && (del == NULL)) {
        //     del = (Node*)removeRec(root, str);
        //     NumElemTree++;
        // }
    }
    if (del != NULL) {
        if (pre == NULL) {
            root = root->right;
            pre = root;
        }
        else if (pre->left == del) {
            pre->left = del->right;
            pre = pre->left;
        }
        else if (pre->right == del) {
            pre->right = del->right;
            pre = pre->right;
        }
        cur = del->left;
    }
    delete del->value;
    delete del;
    if (pre != NULL) {
        while (pre->left != NULL) {
            pre = pre->left;
        }
        pre->left = cur;
    }
    for (int i = 0; i < 4; i++) {
        delete[] dataTab[i];
    }
    delete[] dataTab;
}

template<class T>
void BinTree<T>::removeTreeRec(Node* del) {
    if (del->left != NULL) {
        removeTreeRec(del->left);
        delete del->left;
    }
    if (del->right != NULL) {
        removeTreeRec(del->right);
        delete del->right;
    }
    delete del->value;
}

template<class T>
void BinTree<T>::removeAll() {
    removeTreeRec(root);
    delete root;
    root = NULL;
    cur = NULL;
}
