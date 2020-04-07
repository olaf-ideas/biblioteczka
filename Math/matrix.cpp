template<class T>
class Matrix{
public:

	Matrix(){}
  Matrix(size_t n, size_t m, T def = 0):mx(n,std::vector<T>(m,def)){}
  Matrix(std::vector<std::vector<T>> _mx):mx(_mx){}

  friend Matrix operator * (const Matrix& a, const Matrix& b){
    assert(a.row_size() == b.col_size());

    Matrix c(a.col_size(), b.row_size());
    for(size_t i = 0; i < a.col_size(); i++)
      for(size_t j = 0; j < b.row_size(); j++)
        for(size_t k = 0; k < a.row_size(); k++)
          c.mx[i][j] += a.mx[i][k] * b.mx[k][j];
    return c;
  }

  Matrix operator *= (const Matrix& other){
    *this = *this * other;
    return *this;
  }

  friend Matrix operator + (const Matrix& a, const Matrix& b){
    assert(a.col_size() == b.col_size() && a.row_size() == b.row_size());
    Matrix c(a.col_size(), b.col_size());
    for(size_t i = 0; i < a.col_size(); i++)
      for(size_t j = 0; j < a.row_size(); j++)
        c.mx[i][j] = a.mx[i][j] + b.mx[i][j];
    return c;
  }

  Matrix operator += (const Matrix& other){
    *this = *this + other;
    return *this;
  }

  friend Matrix operator + (Matrix a, int b){
    for(size_t i = 0; i < a.col_size(); i++)
      for(size_t j = 0; j < a.row_size(); j++)
        a.mx[i][j] += b;
    return b;
  }

  Matrix operator += (int x){
    *this = *this + x;
    return *this;
  }

  friend Matrix operator - (Matrix a, int b){
    for(size_t i = 0; i < a.col_size(); i++)
      for(size_t j = 0; j < a.row_size(); j++)
        a.mx[i][j] -= b;
    return b;
  }

  Matrix operator -= (int x){
    *this = *this - x;
    return *this;
  }

  friend Matrix operator ^ (Matrix a, int b){
    assert(a.col_size() == a.row_size());

    Matrix c(a.col_size(),a.row_size(), 0);
    for(size_t i = 0; i < c.col_size(); i++)  
      c.mx[i][i] = 1;

    for(; b; a *= a, b >>= 1)
      if(b & 1) c *= a;
    return c;
  }

  Matrix operator ^= (int x){
    *this = *this ^ x;
    return *this;
  }

  const size_t col_size() const {
    return mx.size();
  }

  void pass_func (std::function<T(T)> f){
    for(size_t i = 0; i < col_size(); i++)
      for(size_t j = 0; j < row_size(); j++)
        mx[i][j] = f(mx[i][j]);
  }

  const size_t row_size() const {
    if(mx.empty())  return 0;
    return mx[0].size();
  }

  void randomize(std::function<T(int,int)> f){
    for(size_t i = 0; i < col_size(); i++)
      for(size_t j = 0; j < row_size(); j++)
          mx[i][j] = f(i,j);
  }

  friend std::ostream & operator << (std::ostream& o, const Matrix& m){
    o << "[";
    for(size_t i = 0; i < m.col_size()-1; i++){
      o << "[";
      for(size_t j = 0; j < m.row_size()-1; j++)  o << m.mx[i][j] << ", ";
      o << m.mx[i].back() << "]\n";
    }
    o << "[";
    for(size_t j = 0; j < m.row_size()-1; j++)  o << m.mx.back()[j] << ", ";
    o << m.mx.back().back() << "]]";
    return o;
  }

  std::vector<std::vector<T>> mx; 
};

class Layer{
  Matrix<double> weights, bias;
  Layer(size_t n, size_t m):weights(n,m),bias(1,m){}
  void randomize(std::function<double(int, int)> f){
    weights.randomize(f);
    bias.randomize(f);
  }
};

class AI{
private:
  std::vector<Layer> brain;
public:
  AI(std::vector<int> layers){
    for(size_t i = 1; i < layers.size(); i++){
      brain.push_back(Matrix<double>(layers[i-1], layers[i]));
      brain.back().randomize(random);
    }
  }
  friend std::ostream & operator << (std::ostream& o, const AI& ai){
    for(size_t i = 0; i < ai.get_brain().size()-1; i++)  o << ai.get_brain()[i] << ",\n";
    o << ai.get_brain().back();
    return o;
  }

  std::vector<double> predict(std::vector<double> input_data){
      Matrix<double> input(std::vector<std::vector<double>>({input_data}));
      for(size_t i = 0; i < brain.size(); i++)  input *= brain[i], input.pass_func(func);
      return input.mx[0];
  }

  static double func(double x){
    return x / (1 + abs(x));
  }

  static double random(int x, int y){
    return rand() / (RAND_MAX + 0.);
  }

  const std::vector<Matrix<double>>& get_brain() const {
    return brain;
  }
}; 

double fitness(std::vector<double> predict, std::vector<double> output){
  double res = 0;
  for(size_t i = 0; i < predict.size(); i++)  res += abs(predict[i]-output[i]); 
  return res;
}

struct Data{
  std::vector<double> in;
  std::vector<double> out;
  Data(std::vector<double> _in, std::vector<double> _out):in(_in), out(_out){}
};

int main(){
  std::vector<Data> data ({Data({0,0},{0}),Data({1,1},{0}),Data({1,0},{1}),Data({0,1},{1})});
  
  AI best(std::vector<int>({2,5,1}));

  srand(time(NULL));
  std::cout << best << "\n";
  std::cout << best.predict(data[0].in)[0] << "\n";

  return 0;
  double best_fit = 100000000;
  for(int i = 0; i < 1000; i++){
    AI ai(std::vector<int>({2,5,1}));
    double fit = 0;

    for(int j = 0; j < 10; j++, std::random_shuffle(data.begin(), data.end()))
      for(size_t k = 0; k < data.size(); k++) 
        fit += fitness(ai.predict(data[i].in), data[i].out);

    if(best_fit > fit)  best = ai, best_fit = fit;
  }
  std::cout << "[ best fitness: ]" << best_fit << "\n";
}
