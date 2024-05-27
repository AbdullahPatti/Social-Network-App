#pragma once
#include <iostream>
#include "Helper.h"

class Post;
class User;

class Page :public Helper {
private:
	char* page_ID;
	char* title;
	User* PageOwner;
	int TotalLikesOnPage;
	int TotalPostsOfPage;
	Post** Page_Posts;
public:
	Page();
	~Page();
	void setPost(Post& post);
	void SeeThePost(Post& post);
	void setPageId(char* id);
	void setTitle(char* title);
	void SetupPagePosts(int);
	void SeeAllPostsOfPage(int num);
	void setPagePosts(Post* post, int num);
	char* getPageID();
	int getTotalPostPage();
	char* getPageTitle();
	void printPagePosts();
	void printPagePosts2();
};