#include "Page.h"
#include "Post.h"

Page::Page() {
	page_ID = nullptr;
	title = nullptr;
	PageOwner = nullptr;
	TotalLikesOnPage = 0;
	TotalPostsOfPage = 0;
	Page_Posts = nullptr;
}

void Page::setPageId(char* id) {
	page_ID = new char[strlen(id) + 1];
	my_strcpy(page_ID, id);
}

char* Page::getPageID() {
	return page_ID;
}

char* Page::getPageTitle() {
	return title;
}

void Page::setTitle(char* t) {
	title = new char[strlen(t) + 1];
	my_strcpy(title, t);
}


void Page::setPagePosts(Post* obj, int index) {

	Page_Posts[index] = obj;
}

void Page::SetupPagePosts(int posts) {
	Page_Posts = new Post * [posts];
	for (int i = 0; i < posts; i++) {
		Page_Posts[i] = new Post();
	}
}

void Page::SeeAllPostsOfPage(int tpp) {
	TotalPostsOfPage = tpp;
}

void Page::printPagePosts() {
	cout << title << endl;
	if (TotalPostsOfPage != 0 || Page_Posts != nullptr) {
		for (int i = 0; i < TotalPostsOfPage; i++) {
			Page_Posts[i]->PrintPostOfPage();
		}
	}

}

int Page::getTotalPostPage() {
	return TotalPostsOfPage;
}


void Page::printPagePosts2() {

	cout << title << endl;

	if (TotalPostsOfPage != 0 || Page_Posts != nullptr) {
		for (int i = 0; i < TotalPostsOfPage; i++) {
			Page_Posts[i]->PrintHomePage2();
		}
	}

}

Page::~Page() {
	delete[] page_ID;
	delete[] title;

	delete PageOwner;

	for (int i = 0; i < TotalPostsOfPage; ++i) {
		delete Page_Posts[i];
	}
	delete[] Page_Posts;
}

