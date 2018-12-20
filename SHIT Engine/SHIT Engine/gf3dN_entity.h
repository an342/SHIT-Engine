#include "SDL.h"

#include "gf3d_text.h"
#include "gf3d_model.h"

// entitystate struct
typedef enum
{
	ES_Idle,
	ES_Seeking,
	ES_Charging,
	ES_Attacking,
	ES_Cooldown,
	ES_Pain,
	ES_Dying,
	ES_Dead         //Auto cleaned up
}EntityState;

#define EntitySoundMax 8

// entity struct
typedef struct Entity_S
{
	Uint8 inuse;
	Uint64 id;

	TextLine name;
	EntityState state;



	Vector3D position;
	Vector3D Rotation;
	Vector3D scale;
	Vector3D scaleCenter;
	Vector3D Velocity;
	Model model;
	
	void(*draw)(struct Entity_S *self);    /**<called after system entity drawing for custom effects*/
	void(*think)(struct Entity_S *self);   /**<called before system updates to make decisions / hand input*/
	void(*update)(struct Entity_S *self);  /**<called after system entity update*/
	int(*touch)(struct Entity_S *self, struct Entity_S *other);/**<when this entity touches another entity*/
	int(*damage)(struct Entity_S *self, int amount, struct Entity_S *source);/**<when this entity takes damage*/
	void(*die)(struct Entity_S *self);     /**<when this entity dies*/
	void(*free)(struct Entity_S *self);     /**<called when the entity is freed for any custom cleanup*/
	int dead;

	// game data
	float health;
	int maxhealth;
	
}Entity;

/**
* @brief initialize entity system
* @param maxEntities limit on number of simultaneously active entities
*/
void gf3dN_entity_system_init(Uint32 maxEntities);

/**
* @brief get a new entity from the system
* @returns NULL when no more entities, or a new valid entity ready to be given data
*/
Entity *gf3dN_entity_new();


/**
* @brief returns an entity back to the system for recycling
* @param self the entity to be freed
*/
void gf3dN_entity_free(Entity *self);

/**
* @brief draw a single entity
* @param self the entity to draw
*/
void gf3dN_entity_draw(Entity *self);

/**
* @brief draw all active entities in the system
*/
void gf3dN_entity_draw_all();
/**
* @brief call all think function for all active entities in the system
*/
void gf3dN_entity_think_all();

/**
* @brief update all active entities in the system
*/
void gf3dN_entity_update_all();

/**
* @brief call before call to collision space update to prep all bodies with their entities
*/
void gf3dN_entity_pre_sync_all();

/**
* @brief call after call to collision space update to get all entities in sync with what happened
*/
void gf3dN_entity_post_sync_all();