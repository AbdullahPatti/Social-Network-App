#include "Post.h"
#include "User.h"
#include "Page.h"
#include"Comment.h"
#include "Date.h"

Post::Post() {
    Post_ID = nullptr;
    Description = nullptr;
    PostingDate = Date();
    OwnerOfPost = nullptr;
    PagePost = nullptr;
    Total_Comments_On_Post = 0;
    UserLiked = new User * [10];
    for (int i = 0; i < 10; i++) {
        UserLiked[i] = new User();
    }
    PageLiked = nullptr;
    CommentssOnAPost = new Comment * [10];
    for (int i = 0; i < 10; i++) {
        CommentssOnAPost[i] = new Comment();
    }
    LikesOnPost = 0;
    Post_Activity = nullptr;
}

void Post::setPostId(char* poid) {
    Post_ID = new char[strlen(poid) + 1];
    my_strcpy(Post_ID, poid);
}

void Post::SetPostingDate(const Date& date) {
    PostingDate = date;
}

const Date& Post::GetPostingDate() const {
    return PostingDate;
}

void Post::SetPostDescription(char* dp) {
    Description = new char[strlen(dp) + 1];
    my_strcpy(Description, dp);
}

void Post::setPostActivity(int at, char* atu) {
    const char* re = nullptr;
    if (at == 1) {
        re = "feeling";
    }
    else if (at == 2) {
        re = "thinking about";
    }
    else if (at == 3) {
        re = "making";
    }
    else if (at == 4) {
        re = "celebrating";
    }

    if (re != nullptr) {
        int len = strlen(re) + strlen(atu) + 1;
        Post_Activity = new char[len];
        my_strcpy(Post_Activity, re);
        my_strcat(Post_Activity, atu);
    }
}

void Post::PrintPostingDate(const Date& pps) {
    pps.PrintDate();
}

char* Post::getActivity() {
    return Post_Activity;
}

void Post::Make_User_Post_Owner(User* owner) {
    OwnerOfPost = owner;
}


void Post::Like_The_Page(Page* pl, int index) {
    PageLiked = new Page * [1];
    for (int i = 0; i < 1; i++) {
        PageLiked[i] = new Page();
    }
    PageLiked[index] = pl;
}

User* Post::getPostOwner() {
    return OwnerOfPost;
}

void Post::AddALike(User* ul, int index) {
    UserLiked[index] = ul;
}

void Post::Print_Users_Who_Liked() {
    //cout << "Liked Users and Pages:" << endl << endl;

    //if (LikesOnPost > 0) {
    //    // Check if users liked the post
    //    if (UserLiked != nullptr) {
    //        for (int i = 0; i < LikesOnPost; i++) {
    //            cout << UserLiked[i]->getUserId() << "-" << UserLiked[i]->getFirstName() << " " << UserLiked[i]->getLastName() << endl;
    //        }
    //    }

    //    // Check if pages liked the post
    //    if (PageLiked != nullptr) {
    //        for (int i = 0; i < LikesOnPost; i++) {
    //            cout << PageLiked[i]->getPageID() << "-" << PageLiked[i]->getPageTitle() << endl;
    //        }
    //    }
    //}
    //else {
    //    cout << "No users and Pages have liked this post." << endl;
    //}
    //cout << endl;
    if (LikesOnPost != 0 && UserLiked != nullptr && PageLiked != nullptr) {
        for (int i = 0; i < 1; i++) {
            cout << PageLiked[i]->getPageID() << "-" << PageLiked[i]->getPageTitle() << endl;
        }
        for (int i = 1; i < LikesOnPost; i++) {
            cout << UserLiked[i]->getUserId() << "-" << UserLiked[i]->getFirstName() << " " << UserLiked[i]->getLastName() << endl;
        }
    }
    else if (LikesOnPost != 0 && UserLiked != nullptr && PageLiked == nullptr) {
        for (int i = 0; i < LikesOnPost; i++) {
            cout << UserLiked[i]->getUserId() << "-" << UserLiked[i]->getFirstName() << " " << UserLiked[i]->getLastName() << endl;
        }
    }
    else {
        cout << "No one has liked this post" << endl;
    }
}


char* Post::getPostId() {
    return Post_ID;
}


void Post::Add_A_Comment(Comment* c, int index) {
    CommentssOnAPost[index] = c;
}

char* Post::getPostDescription() {
    return Description;
}

int Post::getCommentOnAPost() {
    return CommentsOnAPost;
}

void Post::AddCommentOnAPost(int g) {
    CommentsOnAPost = g;
}

void Post::SetActivityType(int a) {
    TypeOfActivity = a;
}

void Post::setCurrentDate1(Date& oh) {
    CurrentDate = oh;
}


void Post::setLikesonPost(int lop) {
    LikesOnPost = lop;
}
int Post::getLikesonAPost() {
    return LikesOnPost;
}

void Post::Make_Page_Post_Owner(Page* owner) {
    PagePost = owner;
}

Page* Post::Get_Page_Owner_Of_Page() {
    return PagePost;
}

int Post::getactType() {
    return TypeOfActivity;
}

void Post::PrintPostOFUser() {
    if (getactType() == 2) {
        cout << "--- " << OwnerOfPost->getFirstName() << " " << OwnerOfPost->getLastName() << " is " << getActivity() << endl;
        cout << "   '" << getPostDescription() << "' ...";
        PrintPostingDate(GetPostingDate());
        for (int i = 0; i < getCommentOnAPost(); i++) {
            cout << "\t\t" << CommentssOnAPost[i]->getCommentorFirstName() << " " << CommentssOnAPost[i]->getCommenterLastName() << " wrote: " << CommentssOnAPost[i]->getCommentDescription() << endl;
        }
    }
    else {
        cout << "--- " << OwnerOfPost->getFirstName() << " " << OwnerOfPost->getLastName() << " shared:" << endl;
        cout << "   '" << getPostDescription() << "' ...";
        PrintPostingDate(GetPostingDate());
        for (int i = 0; i < getCommentOnAPost(); i++) {
            cout << "\t\t" << CommentssOnAPost[i]->getCommentorFirstName() << " " << CommentssOnAPost[i]->getCommenterLastName() << " wrote: " << CommentssOnAPost[i]->getCommentDescription() << endl;
        }

    }

}

void Post::PrintHomePage1() {
    if ((PostingDate.getDay() == CurrentDate.getDay() || PostingDate.getDay() == CurrentDate.getDay() - 1) && PostingDate.getMonth() == CurrentDate.getMonth() && PostingDate.getYear() == CurrentDate.getYear()) {
        PrintPostOFUser();
    }
}

void Post::PrintHomePage2() {
    if ((PostingDate.getDay() == CurrentDate.getDay() || PostingDate.getDay() == CurrentDate.getDay() - 1) && PostingDate.getMonth() == CurrentDate.getMonth() && PostingDate.getYear() == CurrentDate.getYear()) {
        PrintPostOfPage();
    }
}

void Post::PrintPostOfPage() {
    if (getactType() == 2) {
        cout << "--- " << PagePost->getPageTitle() << " " << " is " << getActivity() << ". ...";
        PrintPostingDate(GetPostingDate());
        cout << "   '" << getPostDescription() << "'" << endl;
        for (int i = 0; i < getCommentOnAPost(); i++) {
            if (CommentssOnAPost[i]->getCommentorFirstName() != nullptr) {
                cout << "\t\t" << CommentssOnAPost[i]->getCommentorFirstName() << " " << CommentssOnAPost[i]->getCommenterLastName() << " wrote: " << CommentssOnAPost[i]->getCommentDescription() << endl;
            }
            else if (CommentssOnAPost[i]->getCommentorPageTitle() != nullptr) {
                cout << "\t\t" << CommentssOnAPost[i]->getCommentorPageTitle() << " wrote: " << CommentssOnAPost[i]->getCommentDescription() << endl;
            }
        }
    }

    else {
        cout << "--- " << PagePost->getPageTitle() << " " << " shared: ...";
        PrintPostingDate(GetPostingDate());
        cout << "   '" << getPostDescription() << endl;
        for (int i = 0; i < getCommentOnAPost(); i++) {
            if (CommentssOnAPost[i]->getCommentorFirstName() != nullptr) {
                cout << "\t\t" << CommentssOnAPost[i]->getCommentorFirstName() << " " << CommentssOnAPost[i]->getCommenterLastName() << " wrote: " << CommentssOnAPost[i]->getCommentDescription() << endl;
            }
            else if (CommentssOnAPost[i]->getCommentorPageTitle() != nullptr) {
                cout << "\t\t" << CommentssOnAPost[i]->getCommentorPageTitle() << " wrote: " << CommentssOnAPost[i]->getCommentDescription() << endl;
            }
        }
    }
}


Comment** Post::GetCommentsOnAPost() {
    return CommentssOnAPost;
}

    Post::~Post() {
        delete[] Post_ID;
        delete[] Description;

        delete OwnerOfPost;  
        delete PagePost;     

        for (int i = 0; i < LikesOnPost; ++i) {
            delete UserLiked[i];
        }
        delete[] UserLiked;

        for (int i = 0; i < LikesOnPost; ++i) {
            delete PageLiked[i];
        }
        delete[] PageLiked;

        for (int i = 0; i < Total_Comments_On_Post; ++i) {
            delete CommentssOnAPost[i];
        }
        delete[] CommentssOnAPost;

}
