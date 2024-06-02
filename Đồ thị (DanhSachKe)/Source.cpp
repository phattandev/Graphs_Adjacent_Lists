#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Node {
	int dinhke;
	int trongso;
	Node* link;
};

const int MAX = 20;

struct DanhSachKe {
	Node* dsk[MAX];
	int sodinh;
};

bool docDanhSachKe(const char* textFile, DanhSachKe& ds) {
	FILE* f = fopen(textFile, "rt");
	if (f == NULL) return false;
	//Khoi tao ds ke
	for (int i = 0; i < MAX; i++)
		ds.dsk[i] = NULL;

	//Doc so dinh cua danh sach ke
	fscanf(f, "%d", &ds.sodinh);

	//Doc danh sach ke
	for (int i = 0; i < ds.sodinh; i++) {
		int sodinhke;
		fscanf(f, "%d", &sodinhke);

		for (int j = 0; j < sodinhke; j++) {
			//Tao 1 con tro chua dinh ke doc tu file
			Node* p = new Node;
			fscanf(f, "%d%d", &p->dinhke, &p->trongso);
			p->link = NULL;

			if (ds.dsk[i] == NULL)
				ds.dsk[i] = p;
			else {
				Node* temp = ds.dsk[i];
				while (temp->link != NULL)
					temp = temp->link;
				temp->link = p;
			}
		}
	}
}

void xuatDanhSachKe(DanhSachKe ds) {
	for (int i = 0; i < ds.sodinh; i++) {
		cout << "(" << i << "): ";
		Node* p = ds.dsk[i];
		while (p != NULL) {
			cout << "(" << p->dinhke << "," << p->trongso << ") ";
			p = p->link;
		}
		cout << endl;
	}
}

int tinhBacRa(DanhSachKe ds, int u) {
	int count = 0;
	Node* p = ds.dsk[u];
	while (p != NULL) {
		count++;
		p = p->link;
	}
	return count;
}

int tinhBacVao(DanhSachKe ds, int u) {
	int count = 0;
	for (int i = 0; i < ds.sodinh; i++) {
		Node* p = ds.dsk[i];
		while (p != NULL) {
			if (p->dinhke == u) {
				count++;
				break;
			}
			p = p->link;
		}
	}
	return count;
}

//v là đỉnh, u là đỉnh kề
void trongSoLonNhat(DanhSachKe ds, int& v, int& u) {
	Node* max = NULL;
	for (int i = 0; i < ds.sodinh; i++) {
		Node* p = ds.dsk[i];
		while (p != NULL) {
			if (max == NULL)
				max = p;
			else if (p->trongso > max->trongso) {
				max = p;
				v = i;
			}
			p = p->link;
		}
	}
	if(max!=NULL)
		u = max->dinhke;
}

int main() {
	DanhSachKe danhSach;
	if (docDanhSachKe("TextDanhSachKe.txt", danhSach)) {
		cout << "Danh Sach Ke:" << endl;
		xuatDanhSachKe(danhSach);
		cout << endl;
	}
	else {
		cout << "Failed to open file!" << endl;
	}

	int ra, vao;
	cout << "Nhap dinh muon tinh so bac ra: "; cin >> ra;
	cout << "Bac ra cua dinh " << ra << ": " << tinhBacRa(danhSach, ra);
	cout << "\nNhap dinh muon tinh so bac vao: "; cin >> vao;
	cout << "Bac vao cua dinh " << vao << ": " << tinhBacVao(danhSach, vao);

	int v, u;
	trongSoLonNhat(danhSach, v, u);
	cout << "\nDinh co trong so lon nhat: (" << v << "," << u << ")";
	cout << endl << endl;
	return 0;
}