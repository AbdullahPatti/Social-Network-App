#pragma once
#include <iostream>
#include "Date.h"
#include "Helper.h"

class User;
class Date;
class Page;
class Comment;

class Post :public Helper {
private:
	char* Post_ID;
	char* Description;
	User* OwnerOfPost;
	Page* PagePost;
	Date PostingDate;
	Date CurrentDate;
	User** UserLiked;
	Page** PageLiked;
	int CommentsOnAPost;
	int Total_Comments_On_Post;
	Comment** CommentssOnAPost;
	int LikesOnPost;
	char* Post_Activity;
	int TypeOfActivity;
public:
	Post();
	~Post();
	void AddALike(User*, int index);
	void Like_The_Page(Page*, int index);
	void Add_A_Comment(Comment*, int);
	void SetPostDescription(char* desc);
	char* getPostDescription();
	void AddCommentOnAPost(int num);
	int getCommentOnAPost();
	void Print_Comments_On_A_Post();
	void PrintPostOFUser();
	void PrintPostOfPage();
	void setPostId(char* postid);
	void setLikesonPost(int likes);
	int getLikesonAPost();
	void Make_User_Post_Owner(User* owner);
	void Make_Page_Post_Owner(Page* owner);
	void setPostActivity(int type, char* activity);
	void SetPostingDate(const Date& date);
	char* getActivity();
	char* getPostId();
	const Date& GetPostingDate() const;
	void PrintPostingDate(const  Date&);
	void setCurrentDate1(Date&);
	User* getPostOwner();
	void Print_Users_Who_Liked();
	void SetActivityType(int type);
	int getactType();
	Page* Get_Page_Owner_Of_Page();
	Comment** GetCommentsOnAPost();
	void PrintHomePage1();
	void PrintHomePage2();
};

