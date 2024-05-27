#pragma once
#include <iostream>
#include "Helper.h"

class Page;
class Post;
class Date;
class Memory;

class User :public Helper {
private:
	char* User_ID;
	char* FirstName;
	char* LastName;
	Page** Pages_Liked_By_User;
	User** UserFriends;
	Post** UserTimeLine;
	Post** Posts_Of_User;
	Memory** memory;
	int totalLikedPagesOfUser;
	int totalPostUser;
	int MemoriesCount;
	int totalUserFriends;
public:
	User();
	~User();
	void Set_Total_Posts_Of_User(int num);
	void SetupPostsOfUser(int num);
	int gettotalPostUser();
	void PrintUserFriends();
	void PrintLikedPagesOfUser();
	void printTimeline();
	void SetupFriendsList(int total);
	char* getFriend(int index);
	void shareMemory(Post* post, const char* text);
	void setFriend(User* user, int index);
	void setPageLike(Page* page, int index);
	void printTimeline2();
	void printHomePageOfUser();
	void setTotalFriends(int friends);
	void setUserId(const char* id);
	void SetupLikedPages(int total);
	void Set_Num_Of_Liked_Pages(int  friends);
	int GetNumOfLikedPages();
	void SetPostsOfUser(Post* post, int num);
	void setUserFirstName(const char* name);
	void setUserLastName(const char* name);
	char* getUserId();
	char* getFirstName();
	char* getLastName();
	int getTotalFriends();
};