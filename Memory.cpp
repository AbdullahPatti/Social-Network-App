
#include "Memory.h"
#include "Helper.h"

Memory::Memory() {
	mainPost = nullptr;
	Message_Text = nullptr;
}

char* Memory::get_Message_Text() {
	return Message_Text;
}

Post* Memory::getPost() {
	return mainPost;
}

Memory::Memory(Post* post, const char* message) {
	mainPost = post;
	Message_Text = new char[strlen(message) + 1];
	my_strcpy(Message_Text, message);
}

Memory::~Memory() {
	delete mainPost; 

	delete[] Message_Text;
}


