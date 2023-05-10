#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/systems/Systems.h"
#include "../../include/systems/Observer.h"
#include "../../include/components/InputComponent.h"
#include <iostream>


// III.F Add the initialization (to 0) of the entity counter to the initalizers list of this constructor
Game::Game() : paused(false), drawDebug(true), id{ 0 }, useArchetypes(true)
{
	inputHandler = std::make_unique<InputHandler>();
	std::cout << "WASD Control" << std::endl;
	if (!useArchetypes) // if not using archetypes use big array and add systems to logic and graphics system vectors
	{
		// V.B: Create the unique pointer to the Input Handler object.
		logicSystems.push_back(std::make_shared<TTLSystem>());
		logicSystems.push_back(std::make_shared<InputSystem>());
		logicSystems.push_back(std::make_shared<MovementSystem>());
		logicSystems.push_back(std::make_shared<GameplaySystem>());
		logicSystems.push_back(std::make_shared<ColliderSystem>());

		graphicsSystems.push_back(std::make_shared<GraphicsSystem>());
		if (drawDebug) // set to true in initialiser list - change to false if you want to hide the debug 
		{
			graphicsSystems.push_back(std::make_shared<PrintDebugSystem>());
		}
	}
	else
	{
		auto ttl = std::make_shared<TTLSystem>();
		auto input =  std::make_shared<InputSystem>();
		auto movement = std::make_shared<MovementSystem>();
		auto gameplay =  std::make_shared<GameplaySystem>();
		auto collider = std::make_shared<ColliderSystem>();
		auto graphics = std::make_shared<GraphicsSystem>();
		auto debug = std::make_shared<PrintDebugSystem>();

		logicSystems.push_back(collider);
		archetypeManager.addArchetypeSystems(ArchetypeID::StaticEntity, logicSystems, graphics);
		
		logicSystems.clear();
		logicSystems.push_back(input);
		logicSystems.push_back(movement);
		logicSystems.push_back(gameplay);
		logicSystems.push_back(collider);
		archetypeManager.addArchetypeSystems(ArchetypeID::DwarfPlayer, logicSystems, graphics);
		
		logicSystems.clear();
		logicSystems.push_back(ttl);
		logicSystems.push_back(movement);
		archetypeManager.addArchetypeSystems(ArchetypeID::Fireball, logicSystems, graphics);

		if (drawDebug) // add debug system to player and static entities
		{
			archetypeManager.addDebug(ArchetypeID::DwarfPlayer, debug);
			archetypeManager.addDebug(ArchetypeID::StaticEntity, debug);
		}
	}
}

Game::~Game()
{
	
}

void Game::toggleControl()
{
	switch (currentControl)
	{
		case WASD:
		{
			currentControl = ARROWS;
			std::cout << "Arrows Control" << std::endl;
			break;
		}
		case ARROWS:
		{
			currentControl = MOUSE;
			std::cout << "Mouse Control" << std::endl;
			break;
		}
		case MOUSE:
		{
			std::cout << "WASD Control" << std::endl;
			currentControl = WASD;
			break;
		}
	}
	getPlayer()->getInputComponent()->getPlayerInputHander()->updateKeys(currentControl);
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row, std::shared_ptr<GraphicsComponent> graphicsComponentPointer)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	ent->init(filename, itemScale, graphicsComponentPointer);
	ent->setPosition(x + cntrFactor, y + cntrFactor);
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	// II.B Instantiate the unique pointer of type "Board". 
	//     Use the constructor of Board that receives the width and the height for the game grid.
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	// Make sure that the vector of lines is not emtpy. h is the number of lines (height of the level)
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if(w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				// II.C (1/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				//      The parameters are the column (for x) and row (for y) where the tile is to be placed, the scale 
				//      of the tile (you can use the variable "tileScale") and the tile type. TileTypes are 
				//      defined in the enumerator TileType in Tile.h. You DON'T need to pass a filename parameter for the texture.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				// II.C (2/5) Use the function addTile from Board to add a WALL tile to this position.
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x':
			{
				/// III.A Call the function "buildEntityAt" to create a Log pointer. The parameters are the filename to 
				///       the file with the sprite ("img/log.png"), the column and the row where the log should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				/// 
				auto logEntity = buildEntityAt<Log>("./img/log.png", col, row, std::make_shared<SpriteGraphics>());
				addEntity(logEntity);			/// uncomment this (you may have to change "ent" for the name of the pointer you've just created above).
	
				//By default, entities stand on corridors
				// II.C (3/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{

				/// III.B Call the function "buildEntityAt" to create a Potion pointer. The parameters are the filename to 
				///       the file with the sprite ("img/potion.png"), the column and the row where the potion should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				auto potionEntity = buildEntityAt<Potion>("./img/potion.png", col, row, std::make_shared<SpriteGraphics>());
				addEntity(potionEntity);			

				//By default, entities stand on corridors
				// II.C (4/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{

				// IV.B (1/4): Create the player shared pointer.
				player = std::make_shared<Player>();
				manager.init(player);
				

				// IV.B (2/4): Call the function that initializes the Sprite Sheet with a single parameter, a const std::string& filename.
				//			   This string should be "img/DwarfSpriteSheet_data.txt"
				player->setGraphicsPointer(std::make_shared<SpriteSheetGraphics>());
				player->initSpriteSheet("./img/DwarfSpriteSheet_data.txt");

				// IV.B (3/4): Call the function that positions the sprite of the player in the board (Player::positionSprite). 
				//			   Parameters are the row and column where this object goes in the board, the sprite width and height (const int Game::spriteWH) 
				//			   and the scale for the tiles (const float Game::tileScale)

				player->positionSprite(row,col,spriteWH,tileScale); // custom location?
				
				// IV.B (4/4): Call our function to add an entity to a game passing the player that has just been created.
				addEntity(player);
				
				collisionCallbacks[EntityType::POTION] = std::bind(&Player::handlePotionCollision, player.get(), std::placeholders::_1);
				collisionCallbacks[EntityType::LOG] = std::bind(&Player::handleLogCollision, player.get(), std::placeholders::_1);

				//By default, entities stand on corridors:
				// II.C (5/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
				}
			}
			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	// III.I This function adds an entity, received by parameter, to the collection of entities.
	//       This must: i) Increase the entity counter (note: the very first entity should have a ID = 1).
	//		 ii) Assign the ID to the entity received by parameter. iii) Add the entity to the vector of entities of this class.
	id++;
	newEntity->setID(id);
	entities.push_back(newEntity);
}

void Game::handleInput()
{
	// V.C: Call the fucntion that handles the input for the game and retrieve the command returned in a variable.
	//      Then, call the "execute" method of the returned object to run this command.
	auto command = inputHandler->handleInput();
	if (command) {
		command->execute(*this);
	}
}


void Game::update(float elapsed)
{
	if (!isPaused())
	{
		if (!useArchetypes)
		{
			bigArray(elapsed, logicSystems); 
		}
		else
		{
			updateArchetypes(elapsed, SystemType::Logic);
		}
		auto it = entities.begin();
		while (it != entities.end())
		{
			if ((*it) != player) {
				auto entType = (*it)->getEntityType();
				if (entType != EntityType::FIRE)
				{
					if (player->intersects(**it))
					{
						if (collisionCallbacks.count(entType) > 0)
						{
							collisionCallbacks[entType](*it);
						}
					}
				}
			}
			it++;
		}
		it = entities.begin();
		while (it != entities.end())
		{
			if ((*it)->isDeleted())
			{
				it = entities.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	window.update();
}

void Game::render(float elapsed)
{
	//Empty the screen
	window.beginDraw();

	// II.D Call the draw method of the board object passing a pointer to the window.
	board->draw(&window);

	if (!useArchetypes)
	{
		bigArray(elapsed, graphicsSystems);  // the graphical systems
	}
	else
	{
		updateArchetypes(elapsed, SystemType::Graphics);
	}
	// III.J Draw all units. Write a loop that iterates over all entities in this class's vector
	//       and calls the "draw" method in the entities.
	
	
	// <FEEDBACK> This loop is no longer needed if you call bigArray above.
	// <CORRECTED Loop removed


	//Draw FPS
	window.drawGUI(*this);

	//Close up for this frame.
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

// III.G Return the current ID counter.
EntityID Game::getIDCounter()
{
	return id;  //you can delete this once III.G is complete.
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	// III.H Return the pointer to the entity which is in position "idx" of the vector.
	//       You must verify that the index is within the bounds of the vector.

	if (idx < 0 || idx >= entities.size()) {
		// index is out of bounds
		throw std::out_of_range("Index is out of bounds.");
	}
	return entities[idx];
}

void Game::bigArray(float elapsedTime, std::vector<std::shared_ptr<System>> system)
{
	auto it = system.begin();
	while (it != system.end())
	{
		auto it_2 = entities.begin();
		while (it_2 != entities.end())
		{
			if (!(*it_2)->isDeleted())
			{
				if ((*it)->validate((*it_2).get()))
				{
					(*it)->update((*it_2).get(), this, elapsedTime);
				}
			}
			it_2++;
		}
		it++;
	}
}

void Game::updateArchetypes(float _elapsedTime, SystemType _systemType)
{
	auto it = entities.begin();
	while (it != entities.end())
	{
		if (!(*it)->isDeleted())
		{
			auto archetypeSystems = archetypeManager.getSystems((*it)->getArchetypeID(), _systemType); // return appropriate systems vector
			auto it_2 = archetypeSystems.begin();
			while (it_2 != archetypeSystems.end())
			{
				(*it_2)->update((*it).get(), this, _elapsedTime);
				it_2++;
			}
		}
		it++;
	}
}