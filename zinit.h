#ifndef ZINIT_H
#define ZINIT_H

class ZInit
{
	public:
		ZInit();
		static int getFrameRate(){return frameRate;}

	private:
		const static int frameRate = 17;
};

#endif // ZINIT_H
