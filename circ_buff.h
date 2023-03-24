template<typename T>
class circ_buff {
private:
  int begin = 0;
  T* data;

public:
  int length;
  circ_buff(T* data, int len, int begin) {
    this->data = data;
    this->begin = begin;
    length = len;
  }

  circ_buff(int len, int begin) {
    this->begin = begin;
    data = new T[len];
    for (int i = 0; i < len; i++) {
      data[i] = 0;
    }
    length = len;
  }

  T get(int index) {
    int temp = begin + index;
    if ((begin + index) > length - 1) {
      temp = (begin + index) - length;
    }
    return data[temp];
  }

  void add(T value) {
    data[begin] = value;
    if (begin == length - 1) {
      this->begin = 0;
    } else {
      this->begin++;
    }
  }
};