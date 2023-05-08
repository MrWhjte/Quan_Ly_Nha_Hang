#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
#include <Windows.h>
#include <string>
using namespace std;
void SET_COLOR(int color)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

struct HoaDon
{
    int MaPhieu;
    float TongTien;
};

struct HoaDonDonNode
{
    HoaDon hd;
    HoaDonDonNode *next;
};
typedef struct HoaDonDonNode *NodeHoaDon;
// quản lý thực đơn
struct ThucDon
{
    string MaMon, TenMon;
    double GiaTien;
};

struct ThucDonNode
{
    ThucDon td;
    ThucDonNode *next;
};
typedef struct ThucDonNode *NodeThucDon;

NodeThucDon TaoMonAn()
{
    ThucDon td;
    cout << "Nhập thông tin thực đơn\n";
    cout << "Nhập mã món ăn: ";
    cin >> td.MaMon;
    cout << "Nhập tên món ăn: ";
    cin.ignore();
    getline(cin, td.TenMon);
    cout << "Nhập giá tiền món ăn: ";
    cin >> td.GiaTien;
    NodeThucDon temp = new ThucDonNode(); // cấp phát bộ nhớ động
    temp->td = td;
    temp->next = NULL;
    return temp;
}

void ThemMonAn(NodeThucDon &a)
{
    NodeThucDon td = TaoMonAn();
    if (a == NULL)
    {
        a = td;
    }
    else
    {
        td->next = a;
        a = td;
    }
}
void in(ThucDon td)
{
    SET_COLOR(6);
    cout << setw(10) << left << td.MaMon << "\t";
    cout << setw(30) << left << td.TenMon << "\t";
    cout << setw(10) << left << td.GiaTien;
    cout << "\n------------------------------------------------------------\n";
}
void inthucdon(NodeThucDon a)
{
    if (a == NULL)
    {
        cout << "danh sách thực đơn trống\n";
    }
    else
    {
        SET_COLOR(6);
        cout << "Danh sách món ăn hiện có\n";
        cout << setw(10) << left << "Mã Món"
             << "\t" << setw(30) << left << "Tên Món"
             << "\t" << setw(10) << left << "Giá Tiền" << endl;
        cout << "------------------------------------------------------------\n";
        SET_COLOR(7);
        while (a != NULL)
        {
            in(a->td);
            a = a->next;
        }
    }
}
void XoaMonAnThucDon(NodeThucDon &a)
{
    string FoodCode;
    NodeThucDon prev = NULL;
    NodeThucDon curr = a; // khởi tạo con trỏ curr trỏ đến node đầu tiên

    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Danh sách thực đơn đang trống:" << endl;
        SET_COLOR(4);
    }
    else
    {
        inthucdon(a); // in ra danh sách thực đơn hiện tại
        cout << "Nhập mã món muốn xóa: ";
        cin >> FoodCode;
        while (curr != NULL)
        {
            if (curr->td.MaMon == FoodCode) // nếu tìm thấy món ăn cần xóa
            {
                if (prev == NULL) // nếu node cần xóa là node đầu tiên
                {
                    a = curr->next; // cập nhật a trỏ đến node kế tiếp
                }
                else
                {
                    prev->next = curr->next; // cập nhật con trỏ của node trước nó trỏ đến node kế tiếp
                }
                delete curr; // giải phóng bộ nhớ của node đó
                cout << "Đã xóa món ăn có mã " << FoodCode << endl;
                return;
            }
            prev = curr;       // cập nhật con trỏ prev trỏ đến node hiện tại
            curr = curr->next; // cập nhật con trỏ curr trỏ đến node kế tiếp
        }
        cout << "Không tìm thấy món ăn có mã " << FoodCode << endl;
    }
}
string FindFood(NodeThucDon &a, string key)
{
    NodeThucDon tmp = a;
    while (tmp != NULL)
    {
        if (tmp->td.MaMon == key) // nếu tìm thấy món ăn cần xóa
        {
            SET_COLOR(6);
            return tmp->td.TenMon;
            SET_COLOR(7);
        }
        tmp = tmp->next; // tăng biến đếm lên 1
    }
    return 0;
}
int FindCost(NodeThucDon &a, string key)
{
    while (a != NULL)
    {
        if (a->td.MaMon == key) // nếu tìm thấy món ăn cần xóa
        {
            SET_COLOR(6);
            return a->td.GiaTien;
            SET_COLOR(7);
        }
        a = a->next; // tăng biến đếm lên 1
    }
    return 0;
}
void TimMonAn(NodeThucDon &a)
{
    string key;
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Danh sách thực đơn đang trống:" << endl;
        SET_COLOR(4);
    }
    else
    {
        cout << "Nhập mã món ăn cần tìm: ";
        cin >> key;
        if (FindFood(a, key) == "0")
        {
            cout << "Không tìm thấy món ăn có mã: " << key << endl;
            return;
        }
        else
        {

            cout << "Món ăn có mã " << key << " là món: " << FindFood(a, key) << "\n";
        }
    }
}
void ChinhSuaMonAn(NodeThucDon &a)
{
    string key;
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Danh sách thực đơn đang trống:" << endl;
        SET_COLOR(4);
    }
    else
    {
        inthucdon(a);
        cout << "Nhập mã món ăn cần chỉnh sửa: ";
        cin >> key;
        NodeThucDon edit = a;
        while (a != NULL)
        {
            if (edit->td.MaMon == key) // nếu tìm thấy món ăn cần xóa
            {
                cout << "Nhập mã món ăn: ";
                cin >> edit->td.MaMon;
                cout << "Nhập Tên món ăn: ";
                cin.ignore();
                getline(cin, edit->td.TenMon);
                cout << "Nhập giá tiền món ăn: ";
                cin >> edit->td.GiaTien;
                cout << "Đã thay đổi thông tin thực đơn\n";
                return;
            }
            edit = edit->next; // tăng biến đếm lên 1
        }
        SET_COLOR(6);
        cout << "Không tìm thấy món ăn có mã " << key << endl;
        SET_COLOR(7);
    }
}
void SapxepMonAn(NodeThucDon &a)
{
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Danh sách thực đơn đang trống:" << endl;
        SET_COLOR(4);
    }
    else
    {
        for (NodeThucDon i = a; i->next != NULL; i = i->next)
        {
            NodeThucDon min = i;
            for (NodeThucDon j = i->next; j != NULL; j = j->next)
            {
                if (min->td.GiaTien > j->td.GiaTien)
                {
                    min = j;
                }
            }
            ThucDon temp = min->td;
            min->td = i->td;
            i->td = temp;
        }
    }
}
// Gọi Thực đơn
struct GoiMon
{
    string MaMon;
    int SoPhan;
    double ThanhTien, TongTien;
};
struct GoiMonNode
{
    GoiMon gm;
    GoiMonNode *next;
};
typedef struct GoiMonNode *NodeGoiMon;

NodeGoiMon GoiMonAn(NodeThucDon a)
{
    GoiMon gm;
    inthucdon(a);
    cout << "Nhập mã món ăn bạn muốn gọi: ";
    cin >> gm.MaMon;
    cout << "Bạn đã gọi món: " << FindFood(a, gm.MaMon) << "\n"; //  FindFood(a,key) trả về tên món ăn có mã key
    cout << "Vui lòng nhập số phần: ";
    cin >> gm.SoPhan;
    gm.ThanhTien = FindCost(a, gm.MaMon);
    gm.TongTien = gm.ThanhTien * gm.SoPhan;
    NodeGoiMon temp = new GoiMonNode(); // cấp phát bộ nhớ động
    temp->gm = gm;
    temp->next = NULL;
    return temp;
}

void ThemGoiMon(NodeThucDon a, NodeGoiMon &b)
{
    if (a == NULL)
    {
        cout << "Thực đơn hiện tại đang trống\n";
    }
    else
    {
        NodeGoiMon td = GoiMonAn(a);
        if (b == NULL) // nếu node gm chưa có data thì gán lun giá trị vào node 1
        {
            b = td;
        }
        else
        {
            td->next = b;
            b = td;
        }
    }
}
void ingm(GoiMon gm)
{
    SET_COLOR(6);
    cout << setw(10) << left << gm.MaMon << "\t";
    cout << setw(15) << left << gm.SoPhan << "\t";
    cout << setw(15) << left << gm.ThanhTien << "\t";
    cout << setw(10) << left << gm.TongTien << "\n";
    cout << "---------------------------------------------------------\n";
}
void ingoimon(NodeGoiMon a)
{
    if (a == NULL)
    {
        cout << "Bạn chưa gọi món ăn nào\n";
    }
    else
    {
        SET_COLOR(6);
        cout << "Danh sách các món ăn đã gọi\n";
        cout << setw(10) << left << "Mã Món"
             << "\t" << setw(15) << left << "Số Phần"
             << "\t" << setw(15) << left << "Giá tiền"
             << "\t" << setw(10) << left << "Tổng tiền" << endl;
        cout << "---------------------------------------------------------\n";
        SET_COLOR(7);
        while (a != NULL)
        {
            ingm(a->gm);
            a = a->next;
        }
    }
}

void XoaGoiMon(NodeGoiMon &a)
{
    string FoodCode;
    NodeGoiMon prev = NULL;
    NodeGoiMon curr = a; // khởi tạo con trỏ curr trỏ đến node đầu tiên
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Danh sách thực đơn đang trống:" << endl;
        SET_COLOR(4);
    }
    else
    {
        ingoimon(a); // in ra danh sách thực đơn hiện tại
        cout << "Nhập mã món muốn xóa: ";
        cin >> FoodCode;

        while (curr != NULL)
        {
            if (curr->gm.MaMon == FoodCode) // nếu tìm thấy món ăn cần xóa
            {
                if (prev == NULL) // nếu node cần xóa là node đầu tiên
                {
                    a = curr->next; // cập nhật a trỏ đến node kế tiếp
                }
                else
                {
                    prev->next = curr->next; // cập nhật con trỏ của node trước nó trỏ đến node kế tiếp
                }
                delete curr; // giải phóng bộ nhớ của node đó
                cout << "Đã xóa món ăn có mã " << FoodCode << endl;
                return;
            }
            prev = curr;       // cập nhật con trỏ prev trỏ đến node hiện tại
            curr = curr->next; // cập nhật con trỏ curr trỏ đến node kế tiếp
        }
        cout << "Không tìm thấy món ăn có mã " << FoodCode << endl;
    }
}
void chinhsophan(NodeGoiMon &a)
{
    string key;
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Bạn chưa gọi món" << endl;
        SET_COLOR(4);
    }
    else
    {
        ingoimon(a);
        cout << "Nhập mã món ăn cần chỉnh sửa: ";
        cin >> key;
        NodeGoiMon edit = a;
        while (a != NULL)
        {
            if (edit->gm.MaMon == key) // nếu tìm thấy món ăn cần xóa
            {
                cout << "Nhập lại số phần của món có mã: " << key << endl;
                cin >> edit->gm.SoPhan;
                edit->gm.TongTien = edit->gm.ThanhTien * edit->gm.SoPhan;
                cout << "Đã thay đổi thông tin số phần\n";
                return;
            }
            edit = edit->next; // tăng biến đếm lên 1
        }
        SET_COLOR(6);
        cout << "Không tìm thấy món ăn có mã " << key << endl;
        SET_COLOR(7);
    }
}
int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}
/// hóa đơn
NodeHoaDon TaoHoaDon(int key, double money)
{
    HoaDon hd;
    hd.MaPhieu = key;
    hd.TongTien = money;
    NodeHoaDon temp = new HoaDonDonNode(); // cấp phát bộ nhớ động
    temp->hd = hd;
    temp->next = NULL;
    return temp;
}

void ThemHoaDon(NodeHoaDon &a, int key, double money)
{
    NodeHoaDon hd = TaoHoaDon(key, money);
    if (a == NULL)
    {
        a = hd;
    }
    else
    {
        hd->next = a;
        a = hd;
    }
}
double sum(NodeGoiMon tmp)
{
    double sum = 0;
    while (tmp != NULL)
    {
        sum = sum + tmp->gm.TongTien;
        tmp = tmp->next;
    }
    return sum;
}
void TinhTien(NodeGoiMon &a, NodeHoaDon &c)
{

    int id = random(999, 99999);
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Bạn chưa gọi món" << endl;
        SET_COLOR(4);
    }
    else
    {
        cout << "Đã xuất hóa đơn mã hóa đơn của bạn là: ";
        SET_COLOR(5);
        cout << id << "\n";
        SET_COLOR(7);
        cout << "Tổng số tiền cần thanh toán là: ";
        SET_COLOR(5);
        cout << sum(a) << "\n";
        SET_COLOR(7);
        cout << "Để xem chi tiết hóa đơn vào mục phiếu thanh toán để xem\n";
        ThemHoaDon(c, id, sum(a));
        a = NULL;
    }
}
/// hóa đơn
void intt(HoaDon hd)
{
    SET_COLOR(6);
    cout << setw(15) << left << hd.MaPhieu << "\t";
    cout << setw(20) << left << hd.TongTien << "\n";
    cout << "----------------------------------------\n";
}
void InPhieuThanhToan(NodeHoaDon a)
{
    if (a == NULL)
    {
        cout << "Bạn chưa gọi món ăn nào\n";
    }
    else
    {
        SET_COLOR(6);
        cout << "Danh sách các hóa đơn đã gọi\n";
        cout << setw(15) << left << "Mã Phiếu"
             << "\t" << setw(20) << left << "Thành Tiền" << endl;
        cout << "----------------------------------------\n";
        SET_COLOR(7);
        while (a != NULL)
        {
            intt(a->hd);
            a = a->next;
        }
    }
}
int FindBill(NodeHoaDon a, int key)
{
    NodeHoaDon tmp = a;
    while (tmp != NULL)
    {
        if (tmp->hd.MaPhieu == key) // nếu tìm thấy món ăn cần xóa
        {
            SET_COLOR(6);
            return tmp->hd.TongTien;
            SET_COLOR(7);
        }
        tmp = tmp->next; // tăng biến đếm lên 1
    }
    return 0;
}
void TimHoaDon(NodeHoaDon a)
{
    int key;
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Danh sách hóa đơn đang trống:" << endl;
        SET_COLOR(4);
    }
    else
    {
        cout << "Nhập mã hóa đơn cần tìm: ";
        cin >> key;
        if (FindBill(a, key) == 0)
        {
            cout << "Không tìm thấy món ăn có mã: " << key << endl;
            return;
        }
        else
        {
            cout << "Thông tin hóa đơn có mã " << key << "\n";
            SET_COLOR(6);
            cout << setw(15) << left << "Mã Phiếu"
                 << "\t" << setw(20) << left << "Thành Tiền" << endl;
            cout << "----------------------------------------\n";
            cout << setw(15) << left << key << "\t";
            cout << setw(20) << left << FindBill(a, key) << "\n";
        }
    }
}

void SapXepBill(NodeHoaDon &a)
{
    if (a == NULL)
    {
        SET_COLOR(2);
        cout << "Danh sách hóa đơn đang trống:" << endl;
        SET_COLOR(4);
    }
    else
    {
        for (NodeHoaDon i = a; i->next != NULL; i = i->next)
        {
            NodeHoaDon min = i;
            for (NodeHoaDon j = i->next; j != NULL; j = j->next)
            {
                if (min->hd.TongTien > j->hd.TongTien)
                {
                    min = j;
                }
            }
            HoaDon temp = min->hd;
            min->hd = i->hd;
            i->hd = temp;
        }
    }
}
int main()
{
    int cn;
    NodeThucDon a = NULL;
    NodeGoiMon b = NULL;
    NodeHoaDon c = NULL;
    do
    {
        SET_COLOR(7);
        cout << "---------------------------------\n";
        cout << "1.Quản lý thực đơn\n";
        cout << "2.Quản lý Gọi món\n";
        cout << "3.Quản lý phiếu thanh toán\n";
        SET_COLOR(4);
        cout << "Chọn chức năng: ";
        cin >> cn;
        SET_COLOR(7);
        switch (cn)
        {
        case (1):
        {
            int lc1;
            do
            {
                SET_COLOR(7);
                cout << "---------------------------------\n";
                cout << "1.Thêm món ăn vào thực đơn\n";
                cout << "2.In thực đơn\n";
                cout << "3.Xóa món ăn khỏi thực đơn\n";
                cout << "4.Tìm món ăn theo mã\n";
                cout << "5.chỉnh sửa thông tin thực đơn\n";
                cout << "6.Sắp xếp thực đơn theo giá tiền\n";
                cout << "0.trở về tùy chọn trước\n";
                SET_COLOR(4);
                cout << "Chọn chức năng: ";
                cin >> lc1;
                SET_COLOR(7);
                switch (lc1)
                {
                case (1):
                {
                    ThemMonAn(a);
                }
                break;
                case (2):
                {
                    inthucdon(a);
                }
                break;
                case (3):
                {
                    XoaMonAnThucDon(a);
                }
                break;
                case (4):
                {
                    TimMonAn(a);
                }
                break;
                case (5):
                {
                    ChinhSuaMonAn(a);
                }
                break;
                case (6):
                {
                    SapxepMonAn(a);
                }
                break;
                }
            } while (lc1 != 0);
            break;
        }
        case (2):
        {
            int lc2;
            do
            {
                SET_COLOR(7);
                cout << "---------------------------------\n";
                cout << "1.Gọi món ăn từ thực đơn\n";
                cout << "2.Xóa món ăn đã gọi\n";
                cout << "3.Chỉnh sửa số phần món ăn\n";
                cout << "4.Tính tiền\n";
                cout << "5.in các món đã gọi\n";
                cout << "0.trở về tùy chọn trước\n";
                SET_COLOR(4);
                cout << "Chọn chức năng: ";
                cin >> lc2;
                SET_COLOR(7);
                switch (lc2)
                {
                case (1):
                {
                    ThemGoiMon(a, b);
                }
                break;
                case (2):
                {
                    XoaGoiMon(b);
                }
                break;
                case (3):
                {
                    chinhsophan(b);
                }
                break;
                case (4):
                {
                    TinhTien(b, c);
                }
                break;
                case (5):
                {
                    ingoimon(b);
                }
                break;
                }
            } while (lc2 != 0);
            break;
        }
        break;
        case (3):
        {
            int lc3;
            do
            {
                SET_COLOR(7);
                cout << "---------------------------------\n";
                cout << "1.In danh sách phiếu thanh toán\n";
                cout << "2.tìm hóa đơn theo mã\n";
                cout << "3.xắp xếp theo tổng tiền\n";
                cout << "0.trở về tùy chọn trước\n";
                SET_COLOR(4);
                cout << "Chọn chức năng: ";
                cin >> lc3;
                SET_COLOR(7);
                switch (lc3)
                {
                case (1):
                {
                    InPhieuThanhToan(c);
                }
                break;
                case (2):
                {
                    TimHoaDon(c);
                }
                break;
                case (3):
                {
                    SapXepBill(c);
                }
                break;
                }
            } while (lc3 != 0);
            break;
        }
        break;
        }
    } while (cn != 0);
    return 0;
}