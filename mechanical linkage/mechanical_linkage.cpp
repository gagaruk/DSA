#include <iostream>

struct point{
  int x;
  int y;
};

struct page{
  static const int capacity = 64;
  int count = 0;
  point points[capacity];
  page* prev = nullptr;
};

class c_indirectionTable{
  private:
    int _capacity = 128;
    point** _head;
    point** _tail;

    
    int _gap_capacity = 64;
    point*** _gap_slots;
    point*** _gap_tail;

    void _push_to_gap(point** slot){
      if(_gap_tail - _gap_tail >= _capacity){
        resize_array(_gap_slots, _gap_capacity, 2.0);
        _gap_tail = _gap_slots + _gap_capacity;
      }
      *_gap_tail = slot;
      _gap_tail++;

    }
    point** _pop_from_gap(){
      if(_gap_tail - _gap_slots <= _gap_capacity*0.25){
        resize_array(_gap_slots, _gap_capacity, 0.5);
        _gap_tail = _gap_slots + _gap_capacity;
      }
      _gap_tail--;
      return *_gap_tail;
    }

  public:
    c_indirectionTable(){
      _head = new  point*[_capacity];
      _gap_slots = new point**[_gap_capacity];
    }
    ~c_indirectionTable(){
      delete[] _head;
      delete[] _gap_slots;
    }

    void add_point(point* new_point){
      if(_gap_slots != _gap_tail){
        point** table_slot = _pop_from_gap();
        *table_slot = new_point;
      }else{
        *_tail = new_point;
        _tail++;
      }
    }
    void delete_point(point* point_to_delete){
      point** table_addr;
      int table_size = _tail-_head;

      for(int i=0;i<table_size;i++){
        if(*(_head + i)==point_to_delete){
          table_addr = _head+i;
          break;
        }
      }
      
      _push_to_gap(table_addr);
    }

    void delete_point(point** table_addr){
      _push_to_gap(table_addr);
    }
    
    void set_points(point* point_to_change, point* reference_point){
      point** table_addr_to_change;
      int table_size = _tail-_head;

      for(int i=0;i<table_size;i++){
        if(*(_head + i)==point_to_change){
          table_addr_to_change = _head+i;
          break;
        }
      }

      *table_addr_to_change= reference_point;
    }

    void set_points(point** point_to_change, point** reference_point){
      *point_to_change = *reference_point;
    }
};

template <typename T>
void resizeArray(T*& array_ptr, int& current_capacity, double resize_factor);

point* create_point(int x, int y);

c_indirectionTable indirectionTable = c_indirectionTable();

int main(){
  std::string inputString;
  int op;

  std::cout << "Operations:\n";
  std::cout << "1. Add point\n";
  std::cout << "2. Remove point\n";
  std::cout << "3. Display points\n\n";

  std::cout << "Enter operation number: ";  
  std::getline(std::cin, inputString);
  op = std::stoi(inputString);


  while(op < 1 || op > 3){
    std::cout << "Invalid operation number.\n";
    std::cout << "Please enter a valid operation number (1, 2, or 3): ";
    std::getline(std::cin, inputString);
    op = std::stoi(inputString);
  }
  switch(op){
    case 1:{
      std::string x;
      std::string y;

      std::cout << "Add point operation selected.\n\n"; 
      std::cout << "Choose enter coordinates" << std::endl;

      std::cout << "X: ";
      std::getline(std::cin, x);
      std::cout << "Y: ";
      std::getline(std::cin, y);

      point* point = create_point(std::stoi(x), std::stoi(y));
      indirectionTable.add_point(point);

      break;
    }
    case 2:
      std::cout << "Remove point operation selected.\n\n";
      // Remove po
      break;
    case 3:
      std::cout << "Display points operation selected.\n\n";
      // Display points logic here
      break;
    default: 
      break;
  }


  return 0;
}

template <typename T>
void resize_array(T*& array_ptr, int& current_capacity, double resize_factor){
  static const int _growth_factor=2;

  int new_capacity = (current_capacity == 0) ? 8 : current_capacity * _growth_factor;

  T* new_array = new T[new_capacity];
  for(int i=0; i<current_capacity;i++){
    *(new_array+i) = *(array_ptr+i);
  }

  delete[] array_ptr;
  array_ptr = new_array;
  current_capacity = new_capacity;
}

point* create_point(int x, int y){
}