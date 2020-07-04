#include "BinTree.cpp"
#include "Treenode.h"


int main() {
	BinTree<CTreeNode>* obj = new BinTree<CTreeNode>;
	//BinTree<int>* obj1 = new BinTree<int>;
	obj->openFile("Fligth.csv", "rt");
	int count = obj->GetCount();
	for (int i = 0; i < count; i++) {
		obj->addItem();
	}
	obj->PrintAll();
	obj->addApp("London;411;Ghjkls;2.01.2020");
	obj->PrintAll();
	obj->removeNode("New-York3;414;Zsc;4.03.2021");
	obj->PrintAll();
	obj->removeAll();
	obj->PrintAll();
	delete obj;
	//delete obj1;
	return 0;
}