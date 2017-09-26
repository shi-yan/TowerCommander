#include "LostDialog.h"
#include "TextureAtlasManager.h"

namespace AnimalCrackers
{
	namespace TowerDefense
	{

		LostDialog::LostDialog(void):nextButton(NULL),retryButton(NULL),lostTexture(NULL)
		{
			int atlas=TextureAtlasManager::getSingleton().addNew("dd");
			
			lostTexture=new Texture(atlas,12,12,12,12);

			HotSpot::onReleaseDelegate ond;
			ond.bind(this,&LostDialog::onNext);
			nextButton->addOnReleaseHandler(ond);

			HotSpot::onReleaseDelegate ord;
			ord.bind(this,&LostDialog::onRetry);
			retryButton->addOnReleaseHandler(ord);
		}

		LostDialog::~LostDialog(void)
		{
		}
	}
}