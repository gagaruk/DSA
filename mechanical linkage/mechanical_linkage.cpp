#include <iostream>

struct point{
  int x;
  int y;
};

union page_slot{
  point data;
  page_slot* next_free;
};

struct page{
  static const int capacity = 64;
  int count = 0;
  page_slot slots[capacity];
  page* prev = nullptr;
  page_slot* first_free;
};

struct indirectionTable{
  int capacity = 128;
  page_slot** head = new page_slot*[capacity];
  page_slot** tail = head;
};

struct table_gap_slots{
  int capacity = 64;
  page_slot*** head = new page_slot**[capacity];
  page_slot*** tail = head;
};



template <typename T>
void resizeArray(T*& array_ptr, int& current_capacity, double resize_factor);

void create_point(int x, int y);  
page_slot* allocate_point(int x, int y);

void push_to_gap(page_slot** table_slot);
page_slot** pop_from_gap();

void add_to_table(page_slot* new_point);
void delete_from_table(int index);

indirectionTable pointsTable;
table_gap_slots gaps;


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

      create_point(std::stoi(x), std::stoi(y));

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

void create_point(int x, int y){
  page_slot* slot;
  return slot;
}

page_slot* allocate_point_to_page(int x, int y){
  
}

void push_to_gap(page_slot** table_slot){
      if(gaps.head - gaps.tail >= gaps.capacity){
        resize_array(gaps.head, gaps.capacity, 2.0);
        gaps.tail = gaps.head + gaps.capacity;
      }
      *gaps.tail = table_slot;
      gaps.tail++;
}

page_slot** pop_from_gap(){
      if(gaps.tail - gaps.head <= gaps.capacity*0.25){
        resize_array(gaps.head, gaps.capacity, 0.5);
        gaps.tail = gaps.head + gaps.capacity;
      }
      gaps.tail--;
      return *gaps.tail;
}

void add_point_to_table(page_slot* new_point){
  if(gaps.head != gaps.tail){
    page_slot** table_addr = pop_from_gap();
    *table_addr = new_point;
  }else{
    *pointsTable.tail = new_point;
    pointsTable.tail++;
  }
}

void delete_point(int index){
     page_slot** table_addr = pointsTable.head+index;
      *table_addr = nullptr;
      push_to_gap(table_addr);
}

