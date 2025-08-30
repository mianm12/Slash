// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"

#include "Character/SlashCharacter.h"
#include "Components/CapsuleComponent.h"

void AWeapon::Interact_Implementation(AActor* InteractorActor)
{
	IInteractable::Interact_Implementation(InteractorActor);
	
	if (ASlashCharacter * SlashCharacter = Cast<ASlashCharacter>(InteractorActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon::OnSphereOverlapBegin: Overlapping with %s"), *SlashCharacter->GetName());
		GetItemMesh()->AttachToComponent(SlashCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));

		// Ignore collision with the character's capsule to prevent physics issues
		SlashCharacter->GetCapsuleComponent()->IgnoreActorWhenMoving(this, true);
	}
}

void AWeapon::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	// if (ASlashCharacter * SlashCharacter = Cast<ASlashCharacter>(OtherActor))
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Weapon::OnSphereOverlapBegin: Overlapping with %s"), *SlashCharacter->GetName());
	// 	GetItemMesh()->AttachToComponent(SlashCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
	// }
}

void AWeapon::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
