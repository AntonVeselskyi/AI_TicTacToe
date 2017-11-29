#pragma once

#include "AI.h"
namespace AI_TicTacToe
{
	class DllExport AI_Lvl1 : public AI
	{
	public:
		explicit AI_Lvl1(Field &field);
		virtual void MakeATurn() override;

	private:
		virtual void MakeMyMark() override;
		virtual void MakeFirstMark() override {}
	};



	class DllExport AI_Lvl2 : public AI
	{
	public:
		explicit AI_Lvl2(Field &field);
		virtual void MakeATurn() override;

	protected:
		virtual void MakeMyMark() override;

	private:
		virtual void MakeFirstMark() override;
	};

	class DllExport AI_Lvl3 : public AI_Lvl2
	{
	public:
		explicit AI_Lvl3(Field &field);
		virtual void MakeATurn() override;

	private:
		virtual void MakeMyMark() override;
		virtual void MakeFirstMark() override;
		bool MakeSecondMark();
		void OccupyCornerCell();//used in MakeFirstMark() and MakeSecondMark();
		void OccupySideCell();
		void PutMarkNearOpponentsMark();
		bool IsAnyCornerCellMarked();
		int GetPlayerMarksNum();
	};
}