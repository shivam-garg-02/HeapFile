#include <bits/stdc++.h>
using namespace std;

class page
{
public:
    page(int max_page_space){
        no_records = 0;
        max_space = max_page_space;
        available_space = max_space - 16;
    };

    bool insert_data(int record_size, int primary_key){
        if (available_space >= record_size + 4){
            records.push_back({record_size, primary_key});
            no_records++;
            available_space -= (record_size + 4);
            return true;
        }
        else{
            return false;
        }
    };

    int search_return_slot_id(int primary_key){
        for(int i = 0; i < records.size(); i++){
            if (records[i].second == primary_key){
                return i;
            }
        }
        return -1;
    };

    int return_no_records(){
        return no_records;
    }

    // ~page();

private:
    vector<pair<int, int>> records;
    int no_records;
    int max_space;
    int available_space;
};

class heap_file
{
public:
    heap_file(int page_space){
        max_page_space = page_space;
    };

    void insert(int record_size, int primary_key){
        if (pages.size() == 0){
            page* first_page = new page(max_page_space);
            pages.push_back(first_page);
        }
        int i;
        for(i = 0; i < pages.size(); i++){
            if (pages[i]->insert_data(record_size, primary_key) == true){
                break;
            }
        }
        if (i == pages.size()){
            page* new_page = new page(max_page_space);
            new_page->insert_data(record_size, primary_key);
            pages.push_back(new_page);
        }
    };

    pair<int, int> search(int primary_key){
        int i;
        for(i = 0; i < pages.size(); i++){
            int slot_id = pages[i]->search_return_slot_id(primary_key);
            if (slot_id != -1){
                return {i, slot_id};
            }
        }
        return {-1, -1};
    };

    void print_status(){
        cout << pages.size() << " ";
        for(int i = 0; i < pages.size(); i++){
            cout << pages[i]->return_no_records() << " ";
        }
        cout << endl;
    }

    // ~heap_file();

private:
    vector<page*> pages;
    int max_page_space;
};

int main(){
    int max_page_space;
    cin >> max_page_space;

    heap_file my_heap_file(max_page_space);

    int code;
    while(1){
        cin >> code;
        if (code == 1){
            int record_size, primary_key;
            cin >> record_size >> primary_key;
            my_heap_file.insert(record_size, primary_key);
        }
        else if (code == 2){
            my_heap_file.print_status();
        }
        else if (code == 3){
            int primary_key;
            cin >> primary_key;
            pair<int, int> x;
            x = my_heap_file.search(primary_key);
            cout << x.first << " " << x.second << endl;
        }
        else if (code == 4){
            break;
        }
    }
    
    return 0;
}