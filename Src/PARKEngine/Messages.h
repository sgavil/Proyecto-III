#pragma once
#include <stdint.h>
#include <vector>

//En este mismo fichero están las clases de Listener y Emitter para que no haya que incluir 3 ficheros, con este sera
//suficiente ya que todo su contenido tiene que ver con mensajes y su forma de envio

enum MessageId {
	GAME_START,
	GAME_OVER,
	TRANSFORM_CHANGED,
	CITIZEN_OUT,
	CITIZEN_HUNFRY,
	CITIZEN_BORED,
	CITIZEN_HAPPY,
	CITICEN_IN,
	CITICEN_DIRTY,
	ATRACCTION_FULL,
	ATRACCION_EMPTY,
	THEMEPARK_EMPTY,
	THEMEPARK_FULL,
};

typedef uint16_t header_t_;

struct Message {
	Message(MessageId mType, header_t_ size = sizeof(Message)) :
		size_(size), mType_(mType) {
	}
	header_t_ size_;
	uint8_t mType_;
};

//Es muy posible que para varios mensajes haya que hacer un struct para mandar al receptor algo mas que el tipo de mensaje, y por tanto
//a la hora de recibirlo hacer un static_cast para así saber que tipo de mensaje es, ya que todos los stuct heredaran de Message
namespace Architecture
{
	class Listener {
	public:
		Listener() {}
		virtual ~Listener() {};
		virtual void receive(Message* msg) {};
	};

	class Emitter {
	public:
		Emitter() {}
		virtual ~Emitter() {};
		
		//Necesario guardar los posibles receptores de tus mensajes para así no tener que mandarselo a todos
		virtual void registerListener(Listener* o){ listeners_.push_back(o); }
		//Borrar a 
		virtual void removeListener(Listener* o)
		{
			std::vector<Listener*>::iterator position = std::find(listeners_.begin(),
				listeners_.end(), o);
			if (position != listeners_.end())
				listeners_.erase(position);
		}
		virtual void send(Message* msg)
		{
			for (Listener* o : listeners_) {
				o->receive(msg);
			}
		}
	protected:
		std::vector<Listener*> listeners_;
	};
}

