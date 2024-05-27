#pragma once
#include <iostream>
#include "Helper.h"
using namespace std;

class User;
class Post;
class Page;

class Comment :public Helper {
private:
	char* CommentId;
	Post* Comment_On_Post;
	char* Comment_Description;
	User* CommenterUser;
	Page* CommenterPage;
	
public:
	Comment();
	~Comment();
	void setCommentId(char* id);
	void setCommentDescription(char* desc);
	void setCommentOnPost(Post* post);
	char* getCommentorFirstName();
	char* getCommentorPageTitle();
	void setUserCommenter(User*);
	void setPageCommenter(Page*);
	Post* getCommentOnPost();
	char* getCommentId();
	char* getCommenterLastName();
	char* getCommentDescription();
};