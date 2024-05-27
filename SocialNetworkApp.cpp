#include "User.h"
#include "SocialNetworkApp.h"
#include "Page.h"
#include "Post.h"
#include "Comment.h"
#include <fstream>
#include <iostream>
#include <string>
#include"SFML/Graphics.hpp"

void SocialNetworkApp::setTotalpages(int tp) {
    total_Pages = tp;
}

void SocialNetworkApp::setTotalusers(int tu) {
    total_Users = tu;
}

int SocialNetworkApp::getTotalusers() {
    return total_Users;
}

int SocialNetworkApp::getTotalpages() {
    return total_Pages;
}

void SocialNetworkApp::setTotaluserposts(int tpo) {
    total_user_Posts = tpo;
}

int SocialNetworkApp::getTotaluserposts() {
    return total_user_Posts;
}

char* SocialNetworkApp::getFirstnameByuserID(const char* userID) {
    for (int i = 0; i < getTotalusers(); i++) {
        if (my_strcmp(UsersData[i]->getUserId(), userID) == 0) {
            return UsersData[i]->getFirstName();
        }
    }
    return nullptr;
}

void SocialNetworkApp::setTodayDate(Date& oh) {
    current_Date = oh;
}

char* SocialNetworkApp::getPagenameBypageID(const char* userID) {
    for (int i = 0; i < getTotalpages(); i++) {
        if (my_strcmp(PagesData[i]->getPageID(), userID) == 0) {
            return PagesData[i]->getPageTitle();
        }
    }
    return nullptr;
}

void SocialNetworkApp::setTotalcomments(int tc) {
    total_Comments = tc;
}

int SocialNetworkApp::getTotalcomments() {
    return total_Comments;
}

Page* SocialNetworkApp::getWholepageFromPageId(const char* PageID) {
    for (int i = 0; i < getTotalpages(); i++) {
        if (my_strcmp(PagesData[i]->getPageID(), PageID) == 0) {
            return PagesData[i];
        }
    }
    return nullptr;
}

User* SocialNetworkApp::getWholeUserFromuserId(const char* id) {
    for (int i = 0; i < getTotalusers(); i++) {
        if (my_strcmp(UsersData[i]->getUserId(), id) == 0) {
            return UsersData[i];
        }
    }
    return nullptr;
}

char* SocialNetworkApp::getLastNameByuserID(const char* userID) {
    for (int i = 0; i < getTotalusers(); i++) {
        if (my_strcmp(UsersData[i]->getUserId(), userID) == 0) {
            return UsersData[i]->getLastName();
        }
    }
    return nullptr;
}



Post* SocialNetworkApp::getWholePostFrompostId(const char* id) {
    for (int i = 0; i < getTotaluserposts(); i++) {
        if (my_strcmp(PostsData[i]->getPostId(), id) == 0) {
            return PostsData[i];
        }
    }
    return nullptr;
}



void SocialNetworkApp::read() {

    ifstream file("User.txt");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
    }

    int totalusers;
    file >> totalusers;
    setTotalusers(totalusers);
    UsersData = new User * [totalusers];
    for (int i = 0; i < totalusers; i++) {
        UsersData[i] = new User();
    }
    for (int i = 0; i < totalusers; i++) {
        char* temporaryId = new char[5];
        char* temporaryFirstName = new char[20];
        char* temporaryLastName = new char[20];

        file >> temporaryId;
        file >> temporaryFirstName;
        file >> temporaryLastName;

        UsersData[i]->setUserId(temporaryId);
        UsersData[i]->setUserFirstName(temporaryFirstName);
        UsersData[i]->setUserLastName(temporaryLastName);
    }


    ifstream File2("FriendList.txt");
    if (!File2.is_open()) {
        cout << "Error opening file" << endl;
    }

    for (int i = 0; i < totalusers; i++) {

        string friendID;
        int totalFriends = 0;
        File2 >> friendID;
        while (friendID != "-1") {
            totalFriends++;
            File2 >> friendID;
        }

        UsersData[i]->setTotalFriends(totalFriends);
        UsersData[i]->SetupFriendsList(totalFriends);
    }


    File2.clear();
    File2.seekg(0);


    for (int i = 0; i < totalusers; i++) {

        char fID[10];
        char** IDsOfFriends = new char* [UsersData[i]->getTotalFriends()];
        int count = 0;

        File2 >> fID;

        while (my_strcmp(fID, "-1") != 0 && count < UsersData[i]->getTotalFriends()) {
            IDsOfFriends[count] = new char[strlen(fID) + 1];
            my_strcpy(IDsOfFriends[count], fID);
            File2 >> fID;
            count++;
        }
        for (int k = 0; k < UsersData[i]->getTotalFriends(); k++) {
            UsersData[i]->setFriend(getWholeUserFromuserId(IDsOfFriends[k]), k);
        }

        for (int k = 0; k < UsersData[i]->getTotalFriends(); k++) {
            delete[] IDsOfFriends[k];
        }

        delete[] IDsOfFriends;
    }

    ifstream FILE3("Page.txt");

    if (!FILE3.is_open()) {
        cout << "Error opening file" << endl;
    }

    int Total_Pages;
    FILE3 >> Total_Pages;
    setTotalpages(Total_Pages);
    PagesData = new Page * [Total_Pages];
    for (int i = 0; i < Total_Pages; i++) {
        PagesData[i] = new Page();
    }

    for (int i = 0; i < Total_Pages; i++) {
        char* temporary_Page_ID = new char[5];
        FILE3 >> temporary_Page_ID;

        PagesData[i]->setPageId(temporary_Page_ID);

        char* title = new char[50];
        FILE3.ignore();
        FILE3.getline(title, 50);
        PagesData[i]->setTitle(title);
    }


    ifstream FILE4("LikedPages.txt");

    if (!FILE4.is_open()) {
        cout << "Error opening file" << endl;
    }

    for (int i = 0; i < totalusers; i++) {
        int Total_Friends;
        char Page_ID[10];
        FILE4 >> Total_Friends;

        UsersData[i]->Set_Num_Of_Liked_Pages(Total_Friends);
        UsersData[i]->SetupLikedPages(Total_Friends);

        char** pageIDs = new char* [UsersData[i]->GetNumOfLikedPages()];
        int count = 0;

        for (int d = 0; d < UsersData[i]->GetNumOfLikedPages(); d++) {
            FILE4 >> Page_ID;
            pageIDs[count] = new char[strlen(Page_ID) + 1];
            my_strcpy(pageIDs[count], Page_ID);
            count++;
        }

        for (int j = 0; j < UsersData[i]->GetNumOfLikedPages(); j++) {
            UsersData[i]->setPageLike(getWholepageFromPageId(pageIDs[j]), j);
        }

        for (int k = 0; k < UsersData[i]->GetNumOfLikedPages(); k++) {
            delete[] pageIDs[k];
        }
        delete[] pageIDs;
    }
    ifstream FILE5("UserPost.txt");

    if (!FILE5.is_open()) {
        cout << "Error opening file" << endl;
    }

    int User_Posts;
    FILE5 >> User_Posts;
    int Page_Posts;
    FILE5 >> Page_Posts;

    PostsData = new Post * [User_Posts + Page_Posts];
    for (int i = 0; i < User_Posts + Page_Posts; i++) {
        PostsData[i] = new Post();
    }

    setTotaluserposts(User_Posts + Page_Posts);
    for (int i = 0; i < User_Posts; i++) {
        int readAct;
        FILE5 >> readAct;
        PostsData[i]->SetActivityType(readAct);
        if (readAct == 2) {
            char* poid = new char[10];
            FILE5 >> poid;
            PostsData[i]->setPostId(poid);
            int d, mon, y;
            FILE5 >> d >> mon >> y;
            Date postDate(d, mon, y);
            PostsData[i]->SetPostingDate(postDate);
            char* dp = new char[100];
            FILE5.ignore();
            FILE5.getline(dp, 100);
            PostsData[i]->SetPostDescription(dp);
            int actType;
            FILE5 >> actType;
            char* atu = new char[50];
            FILE5.getline(atu, 50);
            PostsData[i]->setPostActivity(actType, atu);
     
            char* powid = new char[5];
            FILE5 >> powid;
            User* owner = getWholeUserFromuserId(powid);
            PostsData[i]->Make_User_Post_Owner(owner);

            char* likedUserId = new char[5];
            int likes = 0;
            while (true) {
                FILE5 >> likedUserId;
                if (my_strcmp(likedUserId, "-1") == 0) {
                    break;
                }
                likes++;
                PostsData[i]->AddALike(getWholeUserFromuserId(likedUserId), likes - 1);
            }
            PostsData[i]->setLikesonPost(likes);

        }
        else {
            PostsData[i]->SetActivityType(1);
            char* poid = new char[10];
            FILE5 >> poid;
            PostsData[i]->setPostId(poid);
            int d, mon, y;
            FILE5 >> d >> mon >> y;
            Date postDate(d, mon, y);
            PostsData[i]->SetPostingDate(postDate);

            char* Description = new char[100];
            FILE5.ignore();
            FILE5.getline(Description, 100);
            PostsData[i]->SetPostDescription(Description);

            char* powid = new char[5];
            FILE5 >> powid;

            User* Owner = getWholeUserFromuserId(powid);
            PostsData[i]->Make_User_Post_Owner(Owner);

            char* likedUserId = new char[5];
            int likes = 0;

            while (true) {
                FILE5 >> likedUserId;
                if (my_strcmp(likedUserId, "-1") == 0) {
                    break;
                }
                likes++;
                PostsData[i]->AddALike(getWholeUserFromuserId(likedUserId), likes - 1);
            }
            PostsData[i]->setLikesonPost(likes);
        }
    }

    ifstream FILE6("PagePost.txt");

    if (!FILE6.is_open()) {
        cout << "Error opening file" << endl;
    }

    for (int i = User_Posts; i < 12; i++) {
        int ActivitiyType;
        FILE6 >> ActivitiyType;
        PostsData[i]->SetActivityType(ActivitiyType);

        if (ActivitiyType == 2) {
            char* poid = new char[5];
            FILE6 >> poid;
            PostsData[i]->setPostId(poid);
            int day, month, year;
            FILE6 >> day >> month >> year;
            Date postDate(day, month, year);

            PostsData[i]->SetPostingDate(postDate);

            char* description = new char[100];
            FILE6.ignore();
            FILE6.getline(description, 100);
            PostsData[i]->SetPostDescription(description);
            int actType;
            FILE6 >> actType;
            char* atu = new char[50];
            FILE6.getline(atu, 50);
            PostsData[i]->setPostActivity(actType, atu);
      
            char* powid = new char[5];
            FILE6 >> powid;
            Page* owner = getWholepageFromPageId(powid);
            PostsData[i]->Make_Page_Post_Owner(owner);

            char* likedPageid = new char[5];
            FILE6 >> likedPageid;
            if (my_strcmp(likedPageid, "-1") != 0) {

                PostsData[i]->Like_The_Page(getWholepageFromPageId(likedPageid), 0);
              

                char* likedUserId = new char[5];
                int likes = 0;
                while (true) {
                    FILE6 >> likedUserId;
                    if (my_strcmp(likedUserId, "-1") == 0) {
                        break;
                    }
                    likes++;
                    PostsData[i]->AddALike(getWholeUserFromuserId(likedUserId), likes);
                }
                PostsData[i]->setLikesonPost(likes + 1);
            }
        }
        else {
            PostsData[i]->SetActivityType(1);

            char* poid = new char[5];
            FILE6 >> poid;
            PostsData[i]->setPostId(poid);

            int day, month, year;
            FILE6 >> day >> month >> year;
            Date postDate(day, month, year);
            PostsData[i]->SetPostingDate(postDate);

            char* description = new char[100];
            FILE6.ignore();
            FILE6.getline(description, 100);
            PostsData[i]->SetPostDescription(description);

            char* powid = new char[5];
            FILE6 >> powid;
            Page* owner = getWholepageFromPageId(powid);
            PostsData[i]->Make_Page_Post_Owner(owner);

            char* likedPageid = new char[5];
            FILE6 >> likedPageid;
            if (my_strcmp(likedPageid, "-1") != 0) {
                PostsData[i]->Like_The_Page(getWholepageFromPageId(likedPageid), 0);

                char* likedUserId = new char[5];
                int likes = 0;
                while (true) {
                    FILE6 >> likedUserId;
                    if (my_strcmp(likedUserId, "-1") == 0) {
                        break;
                    }
                    likes++;
                    PostsData[i]->AddALike(getWholeUserFromuserId(likedUserId), likes);
                }
                PostsData[i]->setLikesonPost(likes + 1);
            }
        }
    }

    ifstream FILE7("Comment.txt");

    if (!FILE7.is_open()) {
        cout << "Error opening file" << endl;
    }

    int TotalComments;
    FILE7 >> TotalComments;
    setTotalcomments(TotalComments);

    for (int i = 0; i < TotalComments; i++) {

        char* copid = new char[10];
        char* Comment_ID = new char[5];
        char* Commenter_ID = new char[5];
        char* Description_Comment = new char[100];
        FILE7 >> copid;
        FILE7 >> Comment_ID;
        FILE7 >> Commenter_ID;
        FILE7.ignore();
        FILE7.getline(Description_Comment, 100);

        Comment* comment = new Comment();

        comment->setCommentId(Comment_ID);
        comment->setCommentDescription(Description_Comment);
        User* userCommenter = getWholeUserFromuserId(Commenter_ID);
        Page* pageCommenter = getWholepageFromPageId(Commenter_ID);
        if (userCommenter != nullptr) {
            comment->setUserCommenter(userCommenter);
        }
        else if (pageCommenter != nullptr) {
            comment->setPageCommenter(pageCommenter);
        }
        Post* post = getWholePostFrompostId(copid);
        post->Add_A_Comment(comment, post->getCommentOnAPost());
        post->AddCommentOnAPost(post->getCommentOnAPost() + 1);
    }

    for (int i = 0; i < totalusers; i++) {
        int p = 0;
        for (int j = 0; j < User_Posts; j++) {
            if (my_strcmp(UsersData[i]->getUserId(), PostsData[j]->getPostOwner()->getUserId()) == 0) {
                p++;
            }
        }
        UsersData[i]->SetupPostsOfUser(p);
        UsersData[i]->Set_Total_Posts_Of_User(p);
    }


    for (int i = 0; i < totalusers; i++) {
        int k = 0;
        for (int j = 0; j < User_Posts; j++) {
            if (my_strcmp(UsersData[i]->getUserId(), PostsData[j]->getPostOwner()->getUserId()) == 0) {
                UsersData[i]->SetPostsOfUser(PostsData[j], k);
                k++;
            }
        }
    }
    for (int i = 0; i < Total_Pages; i++) {
        int k = 0;
        for (int j = User_Posts; j < Page_Posts + User_Posts; j++) {
            if (my_strcmp(PagesData[i]->getPageID(), PostsData[j]->Get_Page_Owner_Of_Page()->getPageID()) == 0) {
                k++;
            }
        }
        PagesData[i]->SetupPagePosts(k);
        PagesData[i]->SeeAllPostsOfPage(k);
    }


    for (int i = 0; i < Total_Pages; i++) {
        int k = 0;
        for (int j = User_Posts; j < Page_Posts + User_Posts; j++) {
            if (my_strcmp(PagesData[i]->getPageID(), PostsData[j]->Get_Page_Owner_Of_Page()->getPageID()) == 0) {
                PagesData[i]->setPagePosts(PostsData[j], k);
                k++;
            }
        }
    }

}

void SocialNetworkApp::printFriendsOfAUser(const char* userId) {
    for (int i = 0; i < getTotalusers(); i++) {
        if (my_strcmp(UsersData[i]->getUserId(), userId) == 0) {
            UsersData[i]->PrintUserFriends();
            break;
        }
    }


}

void SocialNetworkApp::printSpecificUserPages(const char* userId) {
    for (int i = 0; i < getTotalusers(); i++) {
        if (my_strcmp(UsersData[i]->getUserId(), userId) == 0) {
            UsersData[i]->PrintLikedPagesOfUser();
            break;
        }
    }

}

void SocialNetworkApp::printSpecificPostLikes(const char* postId) {
    for (int i = 0; i < total_user_Posts; i++) {
        if (my_strcmp(PostsData[i]->getPostId(), postId) == 0) {
            PostsData[i]->Print_Users_Who_Liked();
            return;
        }
    }
    cout << "Post not found." << endl;
}


void SocialNetworkApp::printSpecificUserPost(const char* postId) {
    for (int i = 0; i < total_user_Posts; i++) {
        if (my_strcmp(PostsData[i]->getPostId(), postId) == 0) {
            PostsData[i]->PrintPostOFUser();
            return;
        }
    }
    cout << "Post not found." << endl;
}

void SocialNetworkApp::PrintPostsOfaPage(const char* postId) {
    for (int i = 0; i < total_user_Posts; i++) {
        if (my_strcmp(PostsData[i]->getPostId(), postId) == 0) {
            PostsData[i]->PrintPostOfPage();
            return;
        }
    }
    cout << "Post not found." << endl;
}

void SocialNetworkApp::SpecificprintUserPosts(const char* userId) {

    for (int i = 0; i < getTotalusers(); i++) {
        if (my_strcmp(UsersData[i]->getUserId(), userId) == 0) {
            UsersData[i]->printTimeline();
        }
    }
}

void SocialNetworkApp::printSpecificHomePage(const char* userId) {

    for (int i = 0; i < getTotalusers(); i++) {
        if (my_strcmp(UsersData[i]->getUserId(), userId) == 0) {
            UsersData[i]->printHomePageOfUser();
        }
    }
}

void SocialNetworkApp::PostsOfASpecificPage(const char* pageId) {
    for (int i = 0; i < getTotalpages(); i++) {
        if (my_strcmp(PagesData[i]->getPageID(), pageId) == 0) {
            PagesData[i]->printPagePosts();
        }
    }
}

bool SocialNetworkApp::userexists(const string& ID) {
    ifstream filing("User.txt");

    int totalusers;
    filing >> totalusers;

    char* temporaryid = new char[6];

    bool check = false;

    for (int i = 0; i < totalusers; i++) {
        filing >> temporaryid;
        if (my_strcmp(temporaryid, ID.c_str()) == 0) {
            check = true;
            break;
        }
    }

    if (check) {
        return true;
    }
    else {
        return false;
    }
}

SocialNetworkApp::~SocialNetworkApp() {
    for (int i = 0; i < total_Pages; i++) {
        delete[] PagesData[i];
    }
    for (int i = 0; i < total_Users; i++) {
        delete[] UsersData[i];
    }
    for (int i = 0; i < total_Comments; i++) {
        delete[] CommentsData[i];
    }
    for (int i = 0; i < total_user_Posts; i++) {
        delete[] PostsData[i];
    }
    delete PostsData;
    delete CommentsData;
    delete UsersData;
    delete PagesData;
}

void SocialNetworkApp::run() {
    int choice = 0;
    char Qn;
    char* currentUser = new char[5];
    char* currentPost = new char[5];
    char* pageView = new char[5];
    char* currentComment = new char[50];
    User* CurrentUser = nullptr;
    Post* PostToBeLikes = nullptr;
    Comment* comm = new Comment();

    Date Current = Date(15, 11, 2017);
    cout << "Today's Date: ";
    Current.PrintDate();
    cout << endl;

    for (int i = 0; i < total_user_Posts; i++) {
        PostsData[i]->setCurrentDate1(Current);
    }

    if (UsersData == nullptr) {
        cout << "User data not loaded." << endl;
        return;
    }


    int option;
    char* idd = nullptr;
    while (idd == nullptr) {
        char* id = new char[6];
        cout << "Enter the id of user: ";
        cin >> id;

        ifstream filing("User.txt");

        int totalusers;
        filing >> totalusers;

        char* temporaryid = new char[6];

        bool check = false;

        for (int i = 0; i < totalusers; i++) {
            filing >> temporaryid;
            if (my_strcmp(temporaryid, id) == 0) {
                check = true;
                break;
            }
        }

        if (check) {
            cout << endl << id << " has been set to current user" << endl;
            idd = new char[strlen(id) + 1];
            my_strcpy(idd, id);
        }
        else {
            cout << endl << "Invalid user id. Please try again." << endl;
        }

    }

   /* cout << endl << "--------------------------------" << endl << endl;
    cout << "Option 1 : View Homepage of a User" << endl;
    cout << "Option 2 : Like a Post" << endl;
    cout << "Option 3 : View List of People Who Have Liked a Post" << endl;
    cout << "Option 4 : Comment on a Post" << endl;
    cout << "Option 5 : View a User Post" << endl;
    cout << "Option 6 : Share a Memory" << endl;
    cout << "Option 7 : View user's timeline" << endl;
    cout << "Option 8 : View friendlist" << endl;
    cout << "Option 9 : View a Page" << endl;
    cout << "Option 10 : View a Page Post" << endl;
    cout << "Option 11 : View a Pages Liked by User" << endl;
    cout << endl << "--------------------------------" << endl << endl;*/
    int x = 0, y = 0;


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Social Network App");
    window.setFramerateLimit(60); // Limit frame rate to 60 FPS

    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Facebook.jpg")) {
        cout << "Failed to load background image!" << endl;
    }

    sf::Texture operations;
    if (!operations.loadFromFile("FACEBOOK1.jpg")) {
        cout << "Error loading Page1.jpg" << endl;
    }

    sf::Texture likePostTexture;
    if (!likePostTexture.loadFromFile("Likepost.jpg")) {
        cout << "Failed to load Likepost.jpg!" << endl;
    }

    sf::Texture Homepage;
    if (!Homepage.loadFromFile("Homepage.jpg")) {
        cout << "Failed to load Homepage.jpg!" << endl;
    }

    sf::Texture ID;
    if (!ID.loadFromFile("ID.jpg")) {
        cout << "Failed to load ID.jpg!" << endl;
    }

    sf::Texture Friends;
    if (!ID.loadFromFile("Friends.jpg")) {
        cout << "Friends List!" << endl;
    }

    sf::Texture Timeline;
    if (!ID.loadFromFile("Timeline.jpg")) {
        cout << "Timeline!" << endl;
    }

    sf::Texture Pages;
    if (!ID.loadFromFile("Pages.jpg")) {
        cout << "Pages" << endl;
    }


    sf::Sprite backgroundImage(backgroundTexture);
    sf::Sprite backgroundOperations(operations);
    sf::Sprite backgroundLikes(likePostTexture);
    sf::Sprite backgroundHomepage(Homepage);
    sf::Sprite backgroundID(ID);
    sf::Sprite backgroundFriend(Friends);
    sf::Sprite backgroundTimeline(Timeline);
    sf::Sprite backgroundPages(Pages);


    // Font loading for text
    sf::Font font;
    if (!font.loadFromFile("BowlbyOne-Regular.ttf")) {
        cout << "Failed to load font!" << endl;
    }

    // Text for user input
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(45);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(780.f, 785.f); // Set position for the text

    string userId; // Variable to store user input
    bool userExists = false;
    bool clicked = false;
    bool task = false;
    // SFML main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 8) { // Backspace
                        if (!userId.empty()) {
                            userId.pop_back();
                            inputText.setString(userId);
                        }

                    }
                    else if (event.text.unicode == 13) { // Enter key
                        // Check if user exists
                        if (userexists(userId)) {
                            userExists = true;
                            userId.clear(); // Clear the user ID when the user exists
                            inputText.setString(""); // Clear the input text
                        }
                        else {
                            cout << "User does not exist!" << endl;
                        }
                    }
                    else {
                        userId += static_cast<char>(event.text.unicode);
                        inputText.setString(userId);
                    }

                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Get the position of the click
                sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
                x = clickPosition.x;
                y = clickPosition.y;
                clicked = true;
            }
        }

        // Drawing operations
        window.clear();

        // Draw background image or Page1.jpg depending on user existence
        if (userExists) {
            window.draw(backgroundOperations);
        }
        else {
            window.draw(backgroundImage);
        }

        // Draw input text
        window.draw(inputText);

        if (clicked && !task) {
            // Draw appropriate texture based on click position
            if (x >= 992 && x <= 1291) {
                if (y >= 79 && y <= 168) {
                    printSpecificHomePage(idd);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 227 && y <= 315) {
                    // Option 2: Like a Post
                    cout << "Enter Post Id you want to like: ";
                    cin >> currentPost;

                    PostToBeLikes = getWholePostFrompostId(currentPost);

                    PostToBeLikes->setLikesonPost(PostToBeLikes->getLikesonAPost() + 1);
                    PostToBeLikes->AddALike(getWholeUserFromuserId(idd), PostToBeLikes->getLikesonAPost()-1);
                    cout << "Post liked Successfully" << endl;
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 375 && y <= 459) {
                    // Option 3: View List of People Who Have Liked a Post
                    cout << "Enter Id of Post you want to See Likes: ";
                    cin >> currentPost;
                    printSpecificPostLikes(currentPost);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 521 && y <= 604) {
                    // Option 4: Comment on a Post
                    cout << "Enter Post Id you want to Comment: ";
                    cin >> currentPost;
                    cout << endl;
                    cout << "Enter your comment: ";
                    cin.ignore();
                    cin.getline(currentComment, 50);
                    PostToBeLikes = getWholePostFrompostId(currentPost);
                    comm->setCommentDescription(currentComment);
                    comm->setUserCommenter(getWholeUserFromuserId(currentUser));
                    comm->setCommentOnPost(PostToBeLikes);
                    PostToBeLikes->AddCommentOnAPost(PostToBeLikes->getCommentOnAPost() + 1);
                    PostToBeLikes->Add_A_Comment(comm, PostToBeLikes->getCommentOnAPost() - 1);
                    cout << "Comment added successfully!" << endl;
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 668 && y <= 754) {
                    // Option 5: View a User Post
                    cout << "Enter Id of Post you want to See: ";
                    cin >> currentPost;
                    cout << endl;
                    printSpecificUserPost(currentPost);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 833 && y <= 917) {
                    // Option 6: Share a Memory
                    cout << "Enter Id of Post you want to See: ";
                    cin >> currentPost;
                    CurrentUser = getWholeUserFromuserId(idd);
                    PostToBeLikes = getWholePostFrompostId(currentPost);
                    CurrentUser->shareMemory(PostToBeLikes, "Very nice");
                    cout << "Memory shared" << endl;
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
            }
            else if (x >= 1452 && x <= 1747) {
                if (y >= 81 && y <= 167) {
                    // Option 7: View user's timeline
                    SpecificprintUserPosts(idd);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 226 && y <= 313) {
                    // Option 8: View friendlist
                    printFriendsOfAUser(idd);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 372 && y <= 461) {
                    // Option 9: View a Page
                    cout << endl;
                    cout << "Enter Page Id you want to See:";
                    cin >> pageView;
                    cout << endl;
                    PostsOfASpecificPage(pageView);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 521 && y <= 605) {
                    // Option 10: View a Page Post
                    cout << "Enter Id of Post you want to See: ";
                    cin >> currentPost;
                    cout << endl;
                    PrintPostsOfaPage(currentPost);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
                else if (y >= 668 && y <= 750) {
                    // Option 11: View a Pages Liked by User
                    printSpecificUserPages(idd);
                    cout << endl << "--------------------------------" << endl << endl;
                    task = true;
                }
            }
        }
        
        if (!task) {
            window.display();
        }
        else {
            // Display the window to show the result of the task
            window.display();

            // Reset task for the next iteration
            task = false;

            // Reset clicked for next input
            clicked = false;
            window.clear();
        }

    }



   /*     int option;
        char* idd = nullptr;
        while (idd == nullptr) {
            char* id = new char[6];
            cout << "Enter the id of user: ";
            cin >> id;

            ifstream filing("User.txt");

            int totalusers;
            filing >> totalusers;

            char* temporaryid = new char[6];

            bool check = false;

            for (int i = 0; i < totalusers; i++) {
                filing >> temporaryid;
                if (my_strcmp(temporaryid, id) == 0) {
                    check = true;
                    break;
                }
            }

            if (check) {
                cout << endl << id << " has been set to current user" << endl;
                idd = new char[strlen(id) + 1];
                my_strcpy(idd, id);
            }
            else {
                cout << endl << "Invalid user id. Please try again." << endl;
            }

        }

        cout << endl << "--------------------------------" << endl << endl;
        cout << "Option 1 : View Homepage of a User" << endl;
        cout << "Option 2 : Like a Post" << endl;
        cout << "Option 3 : View List of People Who Have Liked a Post" << endl;
        cout << "Option 4 : Comment on a Post" << endl;
        cout << "Option 5 : View a User Post" << endl;
        cout << "Option 6 : Share a Memory" << endl;
        cout << "Option 7 : View user's timeline" << endl;
        cout << "Option 8 : View friendlist" << endl;
        cout << "Option 9 : View a Page" << endl;
        cout << "Option 10 : View a Page Post" << endl;
        cout << "Option 11 : View a Pages Liked by User" << endl;
        cout << endl << "--------------------------------" << endl << endl;

        while (true) {
            cout << "Enter the task number you want to perform (1-9), or enter 'x' to terminate: ";
            cin >> option;

            if (option == 'x' || option == 'X') {
                cout << "Terminating the program..." << endl;
                break;
            }

            if (option == 1) {
                printSpecificHomePage(idd);
            }

            else if (option == 2) {
                cout << "Enter Post Id you want to like: ";
                cin >> currentPost;

                PostToBeLikes = getWholePostFrompostId(currentPost);

                PostToBeLikes->setLikesonPost(PostToBeLikes->getLikesonAPost() + 1);
                PostToBeLikes->AddALike(getWholeUserFromuserId(currentUser), PostToBeLikes->getLikesonAPost() - 1);
                cout << "Post liked Successfully" << endl;
            }

            else if (option == 3) {
                cout << "Enter Id of Post you want to See Likes: ";
                cin >> currentPost;
                printSpecificPostLikes(currentPost);
            }

            else if (option == 4) {
                cout << "Enter Post Id you want to Comment: ";
                cin >> currentPost;
                cout << endl;
                cout << "Enter your comment: ";
                cin.ignore();
                cin.getline(currentComment, 50);
                PostToBeLikes = getWholePostFrompostId(currentPost);
                comm->setCommentDescription(currentComment);
                comm->setUserCommenter(getWholeUserFromuserId(currentUser));
                comm->setCommentOnPost(PostToBeLikes);
                PostToBeLikes->AddCommentOnAPost(PostToBeLikes->getCommentOnAPost() + 1);
                PostToBeLikes->Add_A_Comment(comm, PostToBeLikes->getCommentOnAPost() - 1);
                cout << "Comment added successfully!" << endl;
            }
            else if (option == 5) {

                cout << "Enter Id of Post you want to See: ";
                cin >> currentPost;
                cout << endl;
                printSpecificUserPost(currentPost);
                cout << endl << "--------------------------------" << endl << endl;
            }
            else if (option == 6) {

                cout << "Enter Id of Post you want to See: ";
                cin >> currentPost;
                CurrentUser = getWholeUserFromuserId(idd);
                PostToBeLikes = getWholePostFrompostId(currentPost);
                CurrentUser->shareMemory(PostToBeLikes, "Very nice");
                cout << "Memory shared" << endl;
            }
            else if (option == 7) {
                SpecificprintUserPosts(idd);
            }
            else if (option == 8) {
                printFriendsOfAUser(idd);
            }
            else if (option == 9) {
                cout << endl;
                cout << "Enter Page Id you want to See:";
                cin >> pageView;
                cout << endl;
                PostsOfASpecificPage(pageView);
            }
            else if (option == 10) {
                cout << "Enter Id of Post you want to See: ";
                cin >> currentPost;
                cout << endl;
                PrintPostsOfaPage(currentPost);
                cout << endl << "--------------------------------" << endl << endl;
            }
            else if (option == 11) {

                printSpecificUserPages(idd);
            }
            else {
                cout << "Invalid task number. Please enter a number between 2 and 10, or 'x' to terminate." << endl;
            }
        }*/
    }
