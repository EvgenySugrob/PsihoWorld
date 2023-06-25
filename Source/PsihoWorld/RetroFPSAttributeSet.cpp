// Fill out your copyright notice in the Description page of Project Settings.


#include "RetroFPSAttributeSet.h"

URetroFPSAttributeSet::URetroFPSAttributeSet()
{

}

void URetroFPSAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	NewValue = FMath::Clamp<float>(NewValue, 0, 100);
}

bool URetroFPSAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	if (Data.EvaluatedData.Magnitude > 0)
	{

		if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() + AbsoluteMagnitude >= 100)
		{
			SetArmor(100);
			return false;
		}

		if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsoluteMagnitude >= 100)
		{
			SetHealth(100);
			return false;
		}

		//if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetArmor() <= 0)  //Необходимо пофиксить расчет здоровья
		//{																				//Оставив как есть, то при подборе здоровья после урона, здоровье прибаляется к тому значению, которое было изначально
		//	Health.SetCurrentValue(Health.GetCurrentValue() + AbsoluteMagnitude);		//Если добавить эту строку, после подбора брони, здоровье прибавляется к нулевому значению
		//	return false;
		//}

		if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() <= 0)
		{
			SetArmor(0);

		}
	}
	else
	{
		if (Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsoluteMagnitude > GetArmor() && Data.EvaluatedData.Magnitude < 0)
			Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmor()));
	}

	return true;
}
