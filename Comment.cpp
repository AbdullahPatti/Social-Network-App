#include "Comment.h"
#include "User.h"
#include "Post.h"
#include"Page.h"
Comment::Comment() {
	CommentId = nullptr;
	Comment_Description = nullptr;
	CommenterUser = nullptr;
	Comment_On_Post = nullptr;

}

Comment::~Comment() {
	delete[] CommentId;
	delete[] Comment_Description;
	delete[] CommenterPage;
	delete[] CommenterUser;
	delete[] Comment_On_Post;
	delete Comment_On_Post;
	delete CommenterUser;
	delete CommenterPage;

}


void Comment::setCommentId(char* id) {
	CommentId = new char[strlen(id) + 1];
	my_strcpy(CommentId, id);
}

void Comment::setCommentDescription(char* des) {
	Comment_Description = new char[strlen(des) + 1];
	my_strcpy(Comment_Description, des);
}

char* Comment::getCommentId() {
	return CommentId;
}

char* Comment::getCommentDescription() {
	return Comment_Description;
}

void Comment::setUserCommenter(User* obj) {
	CommenterUser = obj;
}

void Comment::setPageCommenter(Page* obj) {
	CommenterPage = obj;
}

void Comment::setCommentOnPost(Post* obj1) {
	Comment_On_Post = obj1;
}

Post* Comment::getCommentOnPost() {
	return Comment_On_Post;
}

char* Comment::getCommentorFirstName() {
	if (CommenterUser != nullptr) {
		return CommenterUser->getFirstName();
	}
	else {
		return nullptr;
	}
}

char* Comment::getCommenterLastName() {
	if (CommenterUser != nullptr) {
		return CommenterUser->getLastName();
	}
	else {
		return nullptr;
	}
}


char* Comment::getCommentorPageTitle() {

	if (CommenterPage != nullptr) {
		return CommenterPage->getPageTitle();
	}
	else {
		return nullptr;
	}
}
