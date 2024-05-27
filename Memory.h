#include <iostream>
#include "Helper.h"
using namespace std;

class Post;

class Memory :public Helper {
private:
	Post* mainPost;
	char* Message_Text;
public:
	Memory();
	~Memory();
	Memory(Post* post, const char* message);
	Post* getPost();
	char* get_Message_Text();
};