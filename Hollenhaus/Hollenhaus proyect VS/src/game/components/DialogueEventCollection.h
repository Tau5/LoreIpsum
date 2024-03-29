#include "../pch.h"
#include "../Namespaces.h"



class DialogueEventCollection
{
public:
	DialogueEventCollection();

	// ChangeScene
	static void ChangeScene(int scene);

	//StartAnimation
	static void StartAnimation();

	//ConfirmationPopUp
	static void ConfirmationPopUp();


	/*template<typename ...Ts>
	void SetFactories(CardFactory* cf, Ts &&... args) {
		cardFactory = cf;
		SetFactories(std::forward<Ts>(args)...);
	}*/


	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto inicial ***

	static std::function<void()> callEvent(
		DialogueEvents::Events index, int scene)
	{
		switch (index)
		{
		case DialogueEvents::None:
			return [scene]
				{
					ChangeScene(scene);
				};
		case DialogueEvents::ChangeScene:
			return []
				{

				};
		case DialogueEvents::StartAnimation:
			return []
				{

				};
		case DialogueEvents::ConfirmMatchPopUp:
			return []
				{
					ConfirmationPopUp();
				};
		default:
			return nullptr;
		}
	}
};
