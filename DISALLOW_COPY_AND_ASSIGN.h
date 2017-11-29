// 禁用编译器默认生成的拷贝构造函数和赋值构造函数
#define DISALLOW_COPY_AND_ASSIGN(ClassName)\
  ClassName(const ClassName &);\
  ClassName& operator=(const ClassName &);
  
// example
class Test
{
public:
  Test();
  ~Test();
  
private:
  DISALLOW_COPY_AND_ASSIGN(Test);
};
