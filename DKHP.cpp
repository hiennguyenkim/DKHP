#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Khai báo lớp 
class HocPhan;
class NguoiDung;
class SinhVien;
class GiangVien;
class HeThongDKHP;

// Lớp cơ sở trừu tượng NguoiDung
class NguoiDung {
protected:
    string ma;        // Mã người dùng 
    string hoTen;     // Họ và tên người dùng
    string matKhau;   // Mật khẩu để đăng nhập
public:
    // Khởi tạo với giá trị mặc định
    NguoiDung(string _ma = "ma", string _hoTen = "hoTen", string _matKhau = "matKhau");
    // Destructor ảo để đảm bảo giải phóng tài nguyên cho lớp con
    virtual ~NguoiDung();
    // Get và set cho các thuộc tính
    string getMa() const;
    void setMa(string _ma);
    string getHoTen() const;
    void setHoTen(string _hoTen);
    string getMatKhau() const;
    void setMatKhau(string _matKhau);
    // Phương thức thuần ảo để thực hiện hành động
    virtual bool ThucHien(HocPhan* hocPhan) = 0;
    // Phương thức thuần ảo để kiểm tra đăng nhập
    virtual bool DangNhap(string inputMa, string inputMk) const = 0;
};

// Triển khai lớp NguoiDungNguoiDung
NguoiDung::NguoiDung(string _ma, string _hoTen, string _matKhau) {
    ma = _ma;
    hoTen = _hoTen;
    matKhau = _matKhau;
}
NguoiDung::~NguoiDung() {}

string NguoiDung::getMa() const { return ma; }
void NguoiDung::setMa(string _ma) { ma = _ma; }
string NguoiDung::getHoTen() const { return hoTen; }
void NguoiDung::setHoTen(string _hoTen) { hoTen = _hoTen; }
string NguoiDung::getMatKhau() const { return matKhau; }
void NguoiDung::setMatKhau(string _matKhau) { matKhau = _matKhau; }

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// Lớp HocPhan, đại diện cho một học phần
class HocPhan {
private:
    string maHocPhan;  // Mã học phần
    string tenHocPhan; // Tên học phần
    int soTinChi;      // Số tín chỉ của học phần
public:
    // Khởi tạo học phần với giá trị mặc định
    HocPhan(string _maHP = "maHP", string _tenHP = "tenHP", int stc = 1);
    // Destructor 
    ~HocPhan();
    // Get và set cho các thuộc tính
    string getMaHocPhan() const;
    void setMaHocPhan(string _maHP);
    string getTenHocPhan() const;
    void setTenHocPhan(string _tenHP);
    int getSoTinChi() const;
    void setSoTinChi(int _stc);
    // Nạp chồng toán tử nhập/xuất để nhập/xuất thông tin học phần
    friend istream& operator>>(istream& in, HocPhan& hp);
    friend ostream& operator<<(ostream& out, const HocPhan& hp);
    // Phương thức hiển thị thông tin học phần
    void HienThiThongTin() const;
    // Nạp chồng toán tử so sánh để kiểm tra hai học phần có cùng mã
    bool operator==(const HocPhan& other) const;
};

// Triển khai lớp HocPhan
HocPhan::HocPhan(string _maHP, string _tenHP, int _stc) {
    maHocPhan = _maHP;
    tenHocPhan = _tenHP;
    soTinChi = _stc;
}

HocPhan::~HocPhan() {}

string HocPhan::getMaHocPhan() const { return maHocPhan; }
void HocPhan::setMaHocPhan(string _maHP) { maHocPhan = _maHP; }
string HocPhan::getTenHocPhan() const { return tenHocPhan; }
void HocPhan::setTenHocPhan(string _tenHP) { tenHocPhan = _tenHP; }
int HocPhan::getSoTinChi() const { return soTinChi; }
void HocPhan::setSoTinChi(int _stc) { soTinChi = _stc; }

istream& operator>>(istream& in, HocPhan& hp) {
    cout << "Nhap ma hoc phan: ";
    in >> hp.maHocPhan;
    cout << "Nhap ten hoc phan: ";
    in.ignore();
    getline(in, hp.tenHocPhan);
    cout << "Nhap so tin chi: ";
    in >> hp.soTinChi;
    return in;
}

ostream& operator<<(ostream& out, const HocPhan& hp) {
    out << "Ma HP: " << hp.maHocPhan << ", Ten HP: " << hp.tenHocPhan << ", So Tin Chi: " << hp.soTinChi;
    return out;
}

void HocPhan::HienThiThongTin() const {
    cout << *this;
}

bool HocPhan::operator==(const HocPhan& other) const {
    return maHocPhan == other.maHocPhan;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// Lớp SinhVien, kế thừa từ NguoiDung
class SinhVien : public NguoiDung {
private:
    vector<HocPhan*> danhSachHocPhanDaDangKy; // Danh sách con trỏ đến học phần đã đăng ký
public:
    // Khởi tạo sinh viên
    SinhVien(string _ma = "ma", string _hoTen = "hoTen", string _matKhau = "matKhau");
    // Destructor
    ~SinhVien();
    // Ghi đè phương thức đăng nhập
    bool DangNhap(string inputMa, string inputMk) const override;
    // Tính tổng số tín chỉ của các học phần đã đăng ký
    int TinhTongTinChi() const;
    // Ghi đè phương thức thực hiện (đăng ký học phần)
    bool ThucHien(HocPhan* hocPhan) override;
    // Đăng ký học phần
    bool DangKyMonHoc(HocPhan* hp);
    // Hủy đăng ký học phần
    bool HuyDangKyMonHoc(string maHP);
    // Hiển thị danh sách học phần đã đăng ký
    void HienThiCacMonDaDangKy() const;
    // Get danh sách học phần đã đăng ký
    const vector<HocPhan*>& getDanhSachHocPhanDaDangKy() const { return danhSachHocPhanDaDangKy; }
};
// Triển khai lớp SinhVien
// Constructor của SinhVien, gọi constructor của lớp NguoiDung
SinhVien::SinhVien(string _ma, string _hoTen, string _matKhau) : NguoiDung(_ma, _hoTen, _matKhau) {}

SinhVien::~SinhVien() {}
// Kiểm tra thông tin đăng nhập của sinh viên
bool SinhVien::DangNhap(string inputMa, string inputMk) const {
    return (this->ma == inputMa && this->matKhau == inputMk);
}

// Tính tổng số tín chỉ của các học phần đã đăng ký
int SinhVien::TinhTongTinChi() const {
    int currentTongTinChi = 0;
    for (const auto* hp : danhSachHocPhanDaDangKy) {
        if (hp) {
            currentTongTinChi += hp->getSoTinChi();
        }
    }
    return currentTongTinChi;
}

// Thực hiện hành động với học phần (đăng ký học phần)
bool SinhVien::ThucHien(HocPhan* hocPhan) {
    if (hocPhan) {
        cout << "Sinh vien " << getHoTen() << " dang tuong tac voi hoc phan: " << hocPhan->getTenHocPhan() << endl;
        return DangKyMonHoc(hocPhan);
    }
    cout << "Hoc phan khong hop le." << endl;
    return false;
}

// Đăng ký học phần, kiểm tra xem học phần đã đăng ký chưa
bool SinhVien::DangKyMonHoc(HocPhan* hp) {
    if (!hp) {
        cout << "Loi: Hoc phan khong ton tai de dang ky." << endl;
        return false;
    }
    for (const auto* registeredHP : danhSachHocPhanDaDangKy) {
        if (registeredHP && registeredHP->getMaHocPhan() == hp->getMaHocPhan()) {
            cout << "Sinh vien " << getHoTen() << " da dang ky mon hoc " << hp->getTenHocPhan() << " roi." << endl;
            return false;
        }
    }
    danhSachHocPhanDaDangKy.push_back(hp); // Thêm học phần vào danh sách
    cout << "Sinh vien " << getHoTen() << " dang ky thanh cong mon hoc: " << hp->getTenHocPhan() << endl;
    return true;
}

// Hủy đăng ký học phần, xóa học phần khỏi danh sách nếu tồn tại
bool SinhVien::HuyDangKyMonHoc(string maHP) {
    auto it = remove_if(danhSachHocPhanDaDangKy.begin(), danhSachHocPhanDaDangKy.end(),
        [&maHP](const HocPhan* hp) {
            return hp && hp->getMaHocPhan() == maHP;
        });
    if (it != danhSachHocPhanDaDangKy.end()) {
        danhSachHocPhanDaDangKy.erase(it, danhSachHocPhanDaDangKy.end());
        cout << "Sinh vien " << getHoTen() << " huy dang ky thanh cong mon hoc ma: " << maHP << endl;
        return true;
    }
    cout << "Sinh vien " << getHoTen() << " khong tim thay mon hoc ma " << maHP << " trong danh sach da dang ky de huy." << endl;
    return false;
}

// Hiển thị danh sách học phần đã đăng ký và tổng tín chỉ
void SinhVien::HienThiCacMonDaDangKy() const {
    cout << "\n--- Danh sach mon hoc da dang ky cua Sinh Vien: " << getHoTen() << " (Ma: " << getMa() << ") ---" << endl;
    if (danhSachHocPhanDaDangKy.empty()) {
        cout << "Chua dang ky mon hoc nao." << endl;
    }
    else {
        for (const auto* hp : danhSachHocPhanDaDangKy) {
            if (hp) {
                hp->HienThiThongTin();
                cout << endl;
            }
        }
        cout << "Tong so tin chi da dang ky: " << TinhTongTinChi() << endl;
    }
    cout << "----------------------------------------------------" << endl;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// Lớp GiangVien, kế thừa từ NguoiDung
class GiangVien : public NguoiDung {
private:
    string monPhuTrach; // Môn học mà giảng viên phụ trách
public:
    // Khởi tạo giảng viên
    GiangVien(string _ma = "ma", string _hoTen = "hoTen", string _matKhau = "matKhau", string _mon = "mon");
    // Destructor 
    ~GiangVien();
    // Ghi đè phương thức đăng nhập
    bool DangNhap(string inputMa, string inputMk) const override;
    // Ghi đè phương thức thực hiện (mở lớp học phần)
    bool ThucHien(HocPhan* hocPhan) override;
    // Get và set cho môn phụ trách
    string getMonPhuTrach() const;
    void setMonPhuTrach(string _mon);
};

// Triển khai lớp GiangVien
// Constructor của GiangVien, gọi constructor của lớp NguoiDung và gán môn phụ trách
GiangVien::GiangVien(string _ma, string _hoTen, string _matKhau, string _mon)
    : NguoiDung(_ma, _hoTen, _matKhau), monPhuTrach(_mon) {
}

// Destructor 
GiangVien::~GiangVien() {}

// Kiểm tra thông tin đăng nhập của giảng viên
bool GiangVien::DangNhap(string inputMa, string inputMk) const {
    return (this->ma == inputMa && this->matKhau == inputMk);
}

// Thực hiện hành động với học phần (mở lớp học phần)
bool GiangVien::ThucHien(HocPhan* hocPhan) {
    if (hocPhan) {
        cout << "Giang vien " << getHoTen() << " (Mon: " << monPhuTrach << ") thuc hien thao tac voi hoc phan: " << hocPhan->getTenHocPhan() << endl;
        return true;
    }
    cout << "Hoc phan khong hop le." << endl;
    return false;
}

// Get và set cho môn phụ trách
string GiangVien::getMonPhuTrach() const { return monPhuTrach; }
void GiangVien::setMonPhuTrach(string _mon) { monPhuTrach = _mon; }

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// Lớp HeThongDKHP
class HeThongDKHP {
private:
    vector<SinhVien*> danhSachSinhVien;      // Danh sách con trỏ đến sinh viên
    vector<GiangVien*> danhSachGiangVien;    // Danh sách con trỏ đến giảng viên
    vector<HocPhan*> danhSachHocPhanHeThong; // Danh sách con trỏ đến học phần
public:
    // Khởi tạo hệ thống
    HeThongDKHP();
    // Destructor 
    ~HeThongDKHP();
    // Khởi tạo dữ liệu mẫu
    void KhoiTao();
    // Hiển thị menu chính
    void HienThiMenuChinh();
    // Xử lý các chức năng cho sinh viên
    void ChucNangSinhVien(SinhVien* sv);
    // Xử lý các chức năng cho giảng viên
    void ChucNangGiangVien(GiangVien* gv);
    // Thêm sinh viên vào hệ thống
    void ThemSinhVien(SinhVien* sv);
    // Tìm sinh viên theo mã
    SinhVien* TimSinhVien(string maSV);
    // Thêm giảng viên vào hệ thống
    void ThemGiangVien(GiangVien* gv);
    // Tìm giảng viên theo mã
    GiangVien* TimGiangVien(string maGV);
    // Xử lý đăng nhập
    NguoiDung* DangNhapHeThong();
    // Thêm học phần vào hệ thống
    void ThemHocPhanVaoHeThong(HocPhan* hp);
    // Tìm học phần theo mã
    HocPhan* TimHocPhanTrongHeThong(string maHP);
    // Hiển thị danh sách tất cả học phần
    void HienThiTatCaHocPhanTrongHeThong() const;
    // Đăng ký học phần cho sinh viên
    bool DangKyMonHocChoSinhVien(string maSV, string maHocPhan);
    // Hủy đăng ký học phần cho sinh viên
    bool HuyDangKyMonHocChoSinhVien(string maSV, string maHocPhan);
    // Mở lớp học phần bởi giảng viên
    bool MoLopHocPhanBoiGiangVien(string maGV, string maHocPhan);
};

//Triển khai lớp HeThongDKHP
// Constructor của HeThongDKHP
HeThongDKHP::HeThongDKHP() {}

// Destructor của HeThongDKHP
HeThongDKHP::~HeThongDKHP() {
    for (SinhVien* sv : danhSachSinhVien) {
        delete sv; // Giải phóng từng sinh viên
    }
    danhSachSinhVien.clear();
    for (GiangVien* gv : danhSachGiangVien) {
        delete gv; // Giải phóng từng giảng viên
    }
    danhSachGiangVien.clear();
    for (HocPhan* hp : danhSachHocPhanHeThong) {
        delete hp; // Giải phóng từng học phần
    }
    danhSachHocPhanHeThong.clear();
}

// Khởi tạo dữ liệu mẫu cho hệ thống
void HeThongDKHP::KhoiTao() {
    cout << "He thong dang khoi tao du lieu mau..." << endl;
    // Thêm các học phần mẫu
    ThemHocPhanVaoHeThong(new HocPhan("COMP1013", "Lap Trinh Nang Cao", 3));
    ThemHocPhanVaoHeThong(new HocPhan("COMP1017", "Lap Trinh Huong Doi Tuong", 3));
    ThemHocPhanVaoHeThong(new HocPhan("COMP1802", "Thiet Ke Web", 2));
    // Thêm các sinh viên mẫu
    ThemSinhVien(new SinhVien("5001104013", "Nguyen Dinh Bao", "123456"));
    ThemSinhVien(new SinhVien("5001104108", "Nguyen Dang Nhat", "123456"));
    ThemSinhVien(new SinhVien("5001104137", "Ho Van Tai", "123456"));
    ThemSinhVien(new SinhVien("5001104044", "Nguyen Kim Hien", "123456"));
    // Thêm các giảng viên mẫu
    ThemGiangVien(new GiangVien("khietltn", "Luong Tran Ngoc Khiet", "khietltn", "Lap Trinh Huong Doi Tuong"));
    ThemGiangVien(new GiangVien("namnp", "Nguyen Phuong Nam", "namnp", "Lap Trinh Nang Cao"));
    ThemGiangVien(new GiangVien("trungnq", "Nguyen Quoc Trung", "trungnq", "Thiet Ke Web"));
    cout << "Khoi tao du lieu mau hoan tat." << endl;
    cout << "---------------------------------------" << endl;
}

// Thêm sinh viên vào hệ thống, kiểm tra mã trùng lặp
void HeThongDKHP::ThemSinhVien(SinhVien* sv) {
    if (sv) {
        for (const auto* existing_sv : danhSachSinhVien) {
            if (existing_sv->getMa() == sv->getMa()) {
                cout << "Loi: Sinh vien voi ma " << sv->getMa() << " da ton tai." << endl;
                delete sv; // Giải phóng nếu trùng
                return;
            }
        }
        danhSachSinhVien.push_back(sv);
        cout << "Da them sinh vien: " << sv->getHoTen() << " (Ma: " << sv->getMa() << ")" << endl;
    }
}

// Tìm sinh viên theo mã
SinhVien* HeThongDKHP::TimSinhVien(string maSV) {
    for (SinhVien* sv : danhSachSinhVien) {
        if (sv->getMa() == maSV) {
            return sv;
        }
    }
    return nullptr; // Trả về nullptr nếu không tìm thấy
}

// Thêm giảng viên vào hệ thống
void HeThongDKHP::ThemGiangVien(GiangVien* gv) {
    if (gv) {
        for (const auto* existing_gv : danhSachGiangVien) {
            if (existing_gv->getMa() == gv->getMa()) {
                cout << "Loi: Giang vien voi ma " << gv->getMa() << " da ton tai." << endl;
                delete gv; // Giải phóng nếu trùng
                return;
            }
        }
        danhSachGiangVien.push_back(gv);
        cout << "Da them giang vien: " << gv->getHoTen() << " (Ma: " << gv->getMa() << ")" << endl;
    }
}

// Tìm giảng viên theo mã
GiangVien* HeThongDKHP::TimGiangVien(string maGV) {
    for (GiangVien* gv : danhSachGiangVien) {
        if (gv->getMa() == maGV) {
            return gv;
        }
    }
    return nullptr; // Trả về nullptr nếu không tìm thấy
}

// Xử lý đăng nhập, kiểm tra mã và mật khẩu cho sinh viên hoặc giảng viên
NguoiDung* HeThongDKHP::DangNhapHeThong() {
    string ma, mk;
    cout << "--- DANG NHAP HE THONG ---" << endl;
    cout << "Nhap ma nguoi dung: ";
    cin >> ma;
    cout << "Nhap mat khau: ";
    cin >> mk;
    for (SinhVien* sv : danhSachSinhVien) {
        if (sv->DangNhap(ma, mk)) {
            cout << "Sinh vien " << sv->getHoTen() << " dang nhap thanh cong." << endl;
            return sv;
        }
    }
    for (GiangVien* gv : danhSachGiangVien) {
        if (gv->DangNhap(ma, mk)) {
            cout << "Giang vien " << gv->getHoTen() << " dang nhap thanh cong." << endl;
            return gv;
        }
    }
    cout << "Dang nhap that bai. Ma nguoi dung hoac mat khau khong dung." << endl;
    return nullptr;
}

// Thêm học phần vào hệ thống, kiểm tra mã trùng lặp
void HeThongDKHP::ThemHocPhanVaoHeThong(HocPhan* hp) {
    if (hp) {
        for (const auto* existing_hp : danhSachHocPhanHeThong) {
            if (existing_hp->getMaHocPhan() == hp->getMaHocPhan()) {
                cout << "Loi: Hoc phan voi ma " << hp->getMaHocPhan() << " da ton tai trong he thong." << endl;
                delete hp; // Giải phóng nếu trùng
                return;
            }
        }
        danhSachHocPhanHeThong.push_back(hp);
        cout << "Da them hoc phan vao he thong: " << hp->getTenHocPhan() << " (Ma: " << hp->getMaHocPhan() << ")" << endl;
    }
}

// Tìm học phần theo mã
HocPhan* HeThongDKHP::TimHocPhanTrongHeThong(string maHP) {
    for (HocPhan* hp : danhSachHocPhanHeThong) {
        if (hp->getMaHocPhan() == maHP) {
            return hp;
        }
    }
    return nullptr; // Trả về nullptr nếu không tìm thấy
}

// Hiển thị danh sách tất cả học phần trong hệ thống
void HeThongDKHP::HienThiTatCaHocPhanTrongHeThong() const {
    cout << "\n--- Danh Sach Hoc Phan Co San Trong He Thong ---" << endl;
    if (danhSachHocPhanHeThong.empty()) {
        cout << "Chua co hoc phan nao trong he thong." << endl;
    }
    else {
        for (const auto* hp : danhSachHocPhanHeThong) {
            if (hp) {
                hp->HienThiThongTin();
                cout << endl;
            }
        }
    }
    cout << "----------------------------------------------" << endl;
}

// Đăng ký học phần cho sinh viên theo mã sinh viên và mã học phần
bool HeThongDKHP::DangKyMonHocChoSinhVien(string maSV, string maHocPhan) {
    SinhVien* sv = TimSinhVien(maSV);
    if (!sv) {
        cout << "Khong tim thay sinh vien voi ma: " << maSV << endl;
        return false;
    }
    HocPhan* hp = TimHocPhanTrongHeThong(maHocPhan);
    if (!hp) {
        cout << "Khong tim thay hoc phan voi ma: " << maHocPhan << " trong he thong." << endl;
        return false;
    }
    return sv->DangKyMonHoc(hp);
}

// Hủy đăng ký học phần cho sinh viên theo mã sinh viên và mã học phần
bool HeThongDKHP::HuyDangKyMonHocChoSinhVien(string maSV, string maHocPhan) {
    SinhVien* sv = TimSinhVien(maSV);
    if (!sv) {
        cout << "Khong tim thay sinh vien voi ma: " << maSV << endl;
        return false;
    }
    return sv->HuyDangKyMonHoc(maHocPhan);
}

// Mở lớp học phần bởi giảng viên theo mã giảng viên và mã học phần
bool HeThongDKHP::MoLopHocPhanBoiGiangVien(string maGV, string maHocPhan) {
    GiangVien* gv = TimGiangVien(maGV);
    if (!gv) {
        cout << "Khong tim thay giang vien voi ma: " << maGV << endl;
        return false;
    }
    HocPhan* hp = TimHocPhanTrongHeThong(maHocPhan);
    if (!hp) {
        cout << "Khong tim thay hoc phan voi ma: " << maHocPhan << " trong he thong de mo lop." << endl;
        return false;
    }
    cout << "Giang vien " << gv->getHoTen() << " (Mon: " << gv->getMonPhuTrach() << ")"
        << " da mo lop cho hoc phan: " << hp->getTenHocPhan() << " (Ma: " << hp->getMaHocPhan() << ")" << endl;
    gv->ThucHien(hp);
    return true;
}

// Xử lý menu chức năng cho sinh viên
void HeThongDKHP::ChucNangSinhVien(SinhVien* sv) {
    if (!sv)
        return;
    int luaChonSV;
    string maHP;
    do {
        cout << "\n--- Chao mung Sinh Vien: " << sv->getHoTen() << " ---" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "1. Xem cac hoc phan co san trong he thong" << endl;
        cout << "2. Dang ky hoc phan" << endl;
        cout << "3. Huy dang ky hoc phan" << endl;
        cout << "4. Xem cac hoc phan da dang ky va tong tin chi" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChonSV;
        switch (luaChonSV) {
        case 1:
            HienThiTatCaHocPhanTrongHeThong(); // Hiển thị danh sách học phần
            break;
        case 2:
            HienThiTatCaHocPhanTrongHeThong();
            cout << "Nhap ma hoc phan ban muon dang ky: ";
            cin >> maHP;
            DangKyMonHocChoSinhVien(sv->getMa(), maHP); // Đăng ký học phần
            break;
        case 3:
            sv->HienThiCacMonDaDangKy(); // Hiển thị học phần đã đăng ký
            if (!sv->getDanhSachHocPhanDaDangKy().empty()) {
                cout << "Nhap ma hoc phan ban muon huy dang ky: ";
                cin >> maHP;
                HuyDangKyMonHocChoSinhVien(sv->getMa(), maHP); // Hủy đăng ký
            }
            break;
        case 4:
            sv->HienThiCacMonDaDangKy(); // Hiển thị học phần và tổng tín chỉ
            break;
        case 0:
            cout << "Dang xuat..." << endl; // Đăng xuất
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (luaChonSV != 0);
}

// Xử lý menu chức năng cho giảng viên
void HeThongDKHP::ChucNangGiangVien(GiangVien* gv) {
    if (!gv)
        return;
    int luaChonGV;
    string maHP;
    do {
        cout << "\n--- Chao mung Giang Vien: " << gv->getHoTen() << " (Mon: " << gv->getMonPhuTrach() << ") ---" << endl;
        cout << "1. Xem cac hoc phan co san trong he thong" << endl;
        cout << "2. Mo lop hoc phan (Thuc hien thao tac voi hoc phan)" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChonGV;
        switch (luaChonGV) {
        case 1:
            HienThiTatCaHocPhanTrongHeThong(); // Hiển thị danh sách học phần
            break;
        case 2:
            HienThiTatCaHocPhanTrongHeThong();
            cout << "Nhap ma hoc phan ban muon mo lop/tuong tac: ";
            cin >> maHP;
            MoLopHocPhanBoiGiangVien(gv->getMa(), maHP); // Mở lớp học phần
            break;
        case 0:
            cout << "Dang xuat..." << endl; // Đăng xuất
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (luaChonGV != 0);
}

// Hiển thị menu chính của hệ thống
void HeThongDKHP::HienThiMenuChinh() {
    int luaChon;
    do {
        cout << "\n========= HE THONG DANG KY HOC PHAN =========" << endl;
        cout << "1. Dang Nhap" << endl;
        cout << "2. Hien thi tat ca hoc phan (Khach)" << endl;
        cout << "0. Thoat Chuong Trinh" << endl;
        cout << "=============================================" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;
        if (cin.fail()) { // Xử lý lỗi nhập liệu không phải số
            cin.clear();
            cin.ignore();
            while (cin.get() != '\n');
            cout << "Nhap khong hop le. Vui long nhap so." << endl;
            luaChon = -1;
        }
        switch (luaChon) {
        case 1: {
            NguoiDung* currentUser = DangNhapHeThong(); // Đăng nhập
            if (currentUser) {
                SinhVien* sv = dynamic_cast<SinhVien*>(currentUser);
                if (sv) {
                    ChucNangSinhVien(sv); // Chuyển đến menu sinh viên
                }
                else {
                    GiangVien* gv = dynamic_cast<GiangVien*>(currentUser);
                    if (gv) {
                        ChucNangGiangVien(gv); // Chuyển đến menu giảng viên
                    }
                }
            }
            break;
        }
        case 2:
            HienThiTatCaHocPhanTrongHeThong(); // Hiển thị học phần cho khách
            break;
        case 0:
            cout << "Thoat chuong trinh. Cam on ban da su dung!" << endl; 
            break;
        default:
            if (luaChon != -1)
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (luaChon != 0);
}

int main() {
    HeThongDKHP heThong; // Tạo đối tượng hệ thống
    heThong.KhoiTao();    // Khởi tạo dữ liệu mẫu
    heThong.HienThiMenuChinh(); // Hiển thị menu chính
    return 0;
}
