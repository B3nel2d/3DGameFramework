//======================================================================
//
//	GameError
//
//	ゲーム内のエラーを扱うクラス
//
//======================================================================

#pragma once

#include <string>
#include <exception>

const int WARNING = 1;
const int FATAL_ERROR = -1;

class GameError : public std::exception{
	private:
		int errorCode;
		std::string message;

	public:
		GameError() : errorCode(FATAL_ERROR), message("Undefined Error in game."){}
		GameError(const GameError& error) : exception(error), errorCode(error.errorCode), message(error.message){}
		GameError(int code, const std::string &message) :errorCode(code), message(message){}

		virtual ~GameError(){}

		GameError& operator= (const GameError& rhs){
			exception::operator=(rhs);
			this->errorCode = rhs.errorCode;
			this->message = rhs.message;
		}

		virtual const char* what() const {return this->getMessage();}

		const char* getMessage() const {return message.c_str();}
		int getErrorCode() const {return errorCode;}
};
