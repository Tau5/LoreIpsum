#pragma once

class Entity;

class Component
{
public:
	Component() :
		ent_()
	{}

	virtual ~Component() {};

	// Para pasarle un puntero a su entidad
	inline void setContext(Entity* ent) {
		ent_ = ent;
	}

	// Se invoca al a�adir un componente a una entidad.
	// Para inicializar el componenete si es necesario.
	virtual void initCompomnent() {};

	// Para actualizar el estado
	virtual void update() {};

protected:
	Entity* ent_;
};

