#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/systems/Systems.h"
#include <iostream>


// III.F Add the initialization (to 0) of the entity counter to the initalizers list of this constructor
Game::Game() : paused(false), drawDebug(false), id{ 0 }
{
	// V.B: Create the unique pointer to the Input Handler object.
	inputHandler = std::make_unique<InputHandler>();

	logicSystems.push_back(std::make_shared<TTLSystem>());
	logicSystems.push_back(std::make_shared<InputSystem>());
	logicSystems.push_back(std::make_shared<MovementSystem>());
	logicSystems.push_back(std::make_shared<GameplaySystem>());
	logicSystems.push_back(std::make_shared<ColliderSystem>());

	graphicsSystems.push_back(std::make_shared<GraphicsSystem>());
	if (!drawDebug) // set to false in initialiser list - change to true if you want to see debug 
	{
		graphicsSystems.push_back(std::make_shared<PrintDebugSystem>());
	}
}

Game::~Game()
{
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
				addEntity(potionEntity);			/// uncomment this
				//std::cout << row << " " << col << " " << spriteWH << " " << tileScale << std::endl;

				//By default, entities stand on corridors
				// II.C (4/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{

				// IV.B (1/4): Create the player shared pointer.
				player = std::make_shared<Player>();
				

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
		// handle non-null pointer case
		command->execute(*this);
	}
}


void Game::update(float elapsed)
{
	if (!isPaused())
	{
		bigArray(elapsed, logicSystems); 
		auto it = entities.begin();
		while (it != entities.end())
		{
			if ((*it) != player) {
				if ((*it)->getEntityType() != EntityType::FIRE)
				{
					if (player->intersects(**it))
					{
						auto entType = (*it)->getEntityType();
						std::shared_ptr<PlayerStateComponent> state = std::dynamic_pointer_cast<PlayerStateComponent>(player->getComponent(ComponentID::STATE));
						switch (entType)
						{
						case EntityType::POTION:
						{
							Potion* potion = dynamic_cast<Potion*>((*it).get());
							int	healthRestore = potion->getHealth();
							player->getHealthComp()->changeHealth(healthRestore);
							(*it)->markDeleted();
							std::cout << "Collide with potion (health restored: " << healthRestore << ", player health: " << player->getHealthComp()->getHealth() << ")" << std::endl;
							break;
						}
						case EntityType::LOG:
						{
							if (state->isAttacking() && player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction()) // check this
							{
								Log* log = dynamic_cast<Log*>((*it).get());
								state->addWood(*player, log->getWood());
								(*it)->markDeleted();
								break;
							}
						default:
							break;
						}
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

	bigArray(elapsed, graphicsSystems);  // the graphical systems

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
