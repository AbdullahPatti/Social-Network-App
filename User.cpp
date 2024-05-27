#include "User.h"
#include "Page.h"
#include"Post.h"
#include"Comment.h"
#include "Date.h"
#include "Memory.h"

User::User() {
	User_ID = nullptr;
	FirstName = nullptr;
	LastName = nullptr;
	UserFriends = nullptr;
	Pages_Liked_By_User = nullptr;
	Posts_Of_User = nullptr;
	UserTimeLine = nullptr;
	totalUserFriends = 0;
	totalLikedPagesOfUser = 0;
	totalPostUser = 0;
	memory = nullptr;
	MemoriesCount = 0;
}

void User::setFriend(User* fl, int index) {
	if (index < 0 || index >= totalUserFriends) {
		throw std::out_of_range("Index out of bounds in setFriend");
	}
	UserFriends[index] = fl;
}

char* User::getFriend(int index) {
	if (index < 0 || index >= totalUserFriends) {
		return nullptr;
	}
	return UserFriends[index]->getUserId();
}

void User::setUserFirstName(const char* fn) {
	FirstName = new char[strlen(fn) + 1];
	my_strcpy(FirstName, fn);
}

void User::shareMemory(Post* post, const char* message) {
	memory = new Memory * [MemoriesCount + 1];
	memory[MemoriesCount] = new Memory(post, message);
	MemoriesCount++;
}


void User::setUserLastName(const char* ln) {
	LastName = new char[strlen(ln) + 1];
	my_strcpy(LastName, ln);
}

void User::setUserId(const char* Id) {
	User_ID = new char[strlen(Id) + 1];
	my_strcpy(User_ID, Id);
}

char* User::getUserId() {
	return User_ID;
}

User::~User() {
	delete[] User_ID;
	delete[] FirstName;
	delete[] LastName;

	for (int i = 0; i < totalLikedPagesOfUser; ++i) {
		delete Pages_Liked_By_User[i];
	}
	delete[] Pages_Liked_By_User;

	for (int i = 0; i < totalUserFriends; ++i) {
		delete UserFriends[i];
	}
	delete[] UserFriends;

	for (int i = 0; i < totalPostUser; ++i) {
		delete UserTimeLine[i];
	}
	delete[] UserTimeLine;

	for (int i = 0; i < totalPostUser; ++i) {
		delete Posts_Of_User[i];
	}
	delete[] Posts_Of_User;

	for (int i = 0; i < MemoriesCount; ++i) {
		delete memory[i];
	}
	delete[] memory;
}

void User::Set_Total_Posts_Of_User(int tpu) {
	totalPostUser = tpu;
}

int User::gettotalPostUser() {
	return totalPostUser;
}

void User::SetupPostsOfUser(int tpu) {
	Posts_Of_User = new Post * [tpu];
	for (int i = 0; i < tpu; i++) {
		Posts_Of_User[i] = new Post();
	}
}

char* User::getFirstName() {
	return FirstName;
}

char* User::getLastName() {
	return LastName;
}

int User::getTotalFriends() {
	return totalUserFriends;
}

void User::PrintUserFriends() {
	cout << FirstName << " " << LastName << " : " << "Friend List" << endl;
	cout << endl;
	cout << endl;
	if (totalUserFriends != 0) {
		for (int i = 0; i < totalUserFriends; i++) {
			cout << UserFriends[i]->getUserId() << "-" << UserFriends[i]->getFirstName() << " " << UserFriends[i]->getLastName() << " " << endl;
		}
	}
	else {
		cout << "User has no Friends" << endl;
	}
	cout << endl;
}

void User::PrintLikedPagesOfUser() {
	cout << FirstName << " " << LastName << "-" << "Liked Pages" << endl;
	cout << endl;
	cout << endl;
	if (totalLikedPagesOfUser != 0) {
		for (int i = 0; i < totalLikedPagesOfUser; i++) {
			cout << Pages_Liked_By_User[i]->getPageID() << "-" << Pages_Liked_By_User[i]->getPageTitle() << " " << endl;
		}
	}
	else {
		cout << "User has no Liked Pages" << endl;
	}
	cout << endl;
}

void  User::setTotalFriends(int  tf) {
	totalUserFriends = tf;
}

void User::SetupFriendsList(int t) {
	UserFriends = new  User * [t];
	for (int i = 0; i < t; i++) {
		UserFriends[i] = new User();
	}
}


void User::SetupLikedPages(int t) {
	Pages_Liked_By_User = new  Page * [t];
	for (int i = 0; i < t; i++) {
		Pages_Liked_By_User[i] = new Page();
	}
}

void User::setPageLike(Page* page, int index) {
	if (index < 0 || index >= totalLikedPagesOfUser) {
		throw std::out_of_range("Index out of bound in setFriend");
	}
	Pages_Liked_By_User[index] = page;
}

void User::Set_Num_Of_Liked_Pages(int  friends) {
	totalLikedPagesOfUser = friends;
}

void User::SetPostsOfUser(Post* post, int index) {

	Posts_Of_User[index] = post;
}


int User::GetNumOfLikedPages() {
	return totalLikedPagesOfUser;
}

void User::printTimeline() {
	cout << FirstName << " " << LastName << " : Timeline" << endl <<endl;
	if (totalPostUser != 0 || Posts_Of_User != nullptr) {

		for (int i = 0; i < totalPostUser; i++) {
			Posts_Of_User[i]->PrintPostOFUser();
			if (MemoriesCount != 0) {
				for (int j = 0; j < MemoriesCount; j++) {
					if (Posts_Of_User[i] == memory[j]->getPost()) {
						cout << FirstName << " " << LastName << " shared:" << endl;
						cout << "\t\t" << memory[j]->get_Message_Text() << endl;
					}

				}
			}
		}

	}

}

void User::printTimeline2() {
	cout << endl;
	if (totalPostUser != 0 || Posts_Of_User != nullptr) {
		for (int i = 0; i < totalPostUser; i++) {
			Posts_Of_User[i]->PrintHomePage1();

		}
	}
}


void User::printHomePageOfUser() {
	cout << FirstName << " " << LastName << "-HomePage" << endl;
	if (totalUserFriends != 0) {
		for (int i = 0; i < totalUserFriends; i++) {
			UserFriends[i]->printTimeline2();
		}

	}
	if (totalLikedPagesOfUser != 0) {
		for (int i = 0; i < totalLikedPagesOfUser; i++) {
			Pages_Liked_By_User[i]->printPagePosts2();
		}
	}
}


