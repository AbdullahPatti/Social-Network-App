#pragma once
#include <iostream>
#include "Helper.h"
#include "Date.h"
using namespace std;

class User;
class Page;
class Post;
class Comment;
class Date;

class SocialNetworkApp :public Helper {
private:
	User** UsersData;
	Post** PostsData;
	Page** PagesData;
	Comment** CommentsData;
	int total_Pages;
	int total_Users;
	Date current_Date;
	int total_user_Posts;
	int total_Comments;

public:
	void run();
	void read();
	~SocialNetworkApp();
	void printFriendsOfAUser(const char* userId);
	char* getFirstnameByuserID(const const char* userID);
	char* getLastNameByuserID(const char* userID);
	int getTotalusers();
	char* getPagenameBypageID(const char* userID);
	void printSpecificUserPages(const char* userId);
	void setTotalusers(int totalUsers);
	int getTotaluserposts();
	void setTotalcomments(int totalComments);
	int getTotalcomments();
	int getTotalpages();
	void setTotalpages(int totalPages);
	void setTotaluserposts(int totalUserPosts);
	void printSpecificPostLikes(const char* userId);
	User* getWholeUserFromuserId(const char* id);
	Page* getWholepageFromPageId(const char* pageID);
	void PrintPostsOfaPage(const char* postId);
	void printSpecificUserPost(const char* postId);
	void SpecificprintUserPosts(const char* userId);
	Post* getWholePostFrompostId(const char* id);
	void PostsOfASpecificPage(const char* userId);
	void printSpecificHomePage(const char* userId);
	void setTodayDate(Date& obj);
	bool userexists(const string& Id);
	bool isValidMenuOption(char input) {
		return (input >= '1' && input <= '11');
	}
};