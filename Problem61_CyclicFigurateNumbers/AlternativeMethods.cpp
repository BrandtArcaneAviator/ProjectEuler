///* For loops for polygonal values: */
	//for (lint_t trin{ 45 }; trin <= 140; ++trin) 
	//{
	//	tempTri = calculatePolygonalValue(trin, PolygonalType::triangular);

	//	for (lint_t squaren{ 32 }; squaren <= 99; ++squaren) 
	//	{
	//		tempSquare = calculatePolygonalValue(squaren, PolygonalType::square);

	//		if (checkCyclicPair4digit(tempTri, tempSquare))
	//		{
	//			/* If true, move to next polygonal number: */
	//			for (lint_t pentn{ 26 }; pentn <= 81; ++pentn)
	//			{
	//				tempPent = calculatePolygonalValue(pentn, PolygonalType::pentagonal);

	//				if (checkCyclicPair4digit(tempSquare, tempPent))
	//				{
	//					for (lint_t hexn{ 23 }; hexn <= 70; ++hexn)
	//					{
	//						tempHex = calculatePolygonalValue(hexn, PolygonalType::hexagonal);

	//						if (checkCyclicPair4digit(tempPent, tempHex))
	//						{
	//							for (lint_t heptn{21}; heptn <= 63; ++heptn)
	//							{
	//								tempHept = calculatePolygonalValue(heptn, PolygonalType::heptagonal);

	//								if (checkCyclicPair4digit(tempHex, tempHept))
	//								{
	//									for (lint_t octn{19}; octn <= 58; ++octn)
	//									{
	//										tempOct = calculatePolygonalValue(octn, PolygonalType::octagonal);

	//										/* For last element in cycle, also check against first element: */
	//										if (checkCyclicPair4digit(tempHept, tempOct) && checkCyclicPair4digit(tempOct, tempTri))
	//										{
	//											/* If true, we've found the set so record it: */
	//											cyclicSet.at(0) = tempTri;
	//											cyclicSet.at(1) = tempSquare;
	//											cyclicSet.at(2) = tempPent;
	//											cyclicSet.at(3) = tempHex;
	//											cyclicSet.at(4) = tempHept;
	//											cyclicSet.at(5) = tempOct;
	//											setisFound = true;
	//										}

	//										if (setisFound)
	//										{
	//											break;
	//										}
	//									}
	//								}
	//								
	//								if (setisFound)
	//								{
	//									break;
	//								}
	//							}
	//						}
	//						
	//						if (setisFound)
	//						{
	//							break;
	//						}
	//					}
	//				}
	//				
	//				if (setisFound)
	//				{
	//					break;
	//				}
	//			}
	//		}
	//		
	//		if (setisFound)
	//		{
	//			break;
	//		}
	//	}

	//	if (setisFound)
	//	{
	//		break;
	//	}
	//}


	///* Alternate method including various permutations: */
	//for (lint_t trin{ 45 }; trin <= 140; ++trin)
	//{
	//	tempTri = calculatePolygonalValue(trin, PolygonalType::triangular);

	//	for (lint_t squaren{ 32 }; squaren <= 99; ++squaren)
	//	{
	//		tempSquare = calculatePolygonalValue(squaren, PolygonalType::square);

	//		for (lint_t pentn{ 26 }; pentn <= 81; ++pentn)
	//		{
	//			tempPent = calculatePolygonalValue(pentn, PolygonalType::pentagonal);

	//			for (lint_t hexn{ 23 }; hexn <= 70; ++hexn)
	//			{
	//				tempHex = calculatePolygonalValue(hexn, PolygonalType::hexagonal);

	//				for (lint_t heptn{ 21 }; heptn <= 63; ++heptn)
	//				{
	//					tempHept = calculatePolygonalValue(heptn, PolygonalType::heptagonal);

	//					for (lint_t octn{ 19 }; octn <= 58; ++octn)
	//					{
	//						tempOct = calculatePolygonalValue(octn, PolygonalType::octagonal);

	//						/* Now we set up a permutation: */
	//						cyclicSet.at(0) = tempTri;
	//						cyclicSet.at(1) = tempSquare;
	//						cyclicSet.at(2) = tempPent;
	//						cyclicSet.at(3) = tempHex;
	//						cyclicSet.at(4) = tempHept;
	//						cyclicSet.at(5) = tempOct;

	//						/* Now check this and all other possible permuations: */
	//						do
	//						{
	//							if (checkCyclicPair4digit(cyclicSet.at(0), cyclicSet.at(1)))
	//							{
	//								if (checkCyclicPair4digit(cyclicSet.at(1), cyclicSet.at(2)))
	//								{
	//									if (checkCyclicPair4digit(cyclicSet.at(2), cyclicSet.at(3)))
	//									{
	//										if (checkCyclicPair4digit(cyclicSet.at(3), cyclicSet.at(4)))
	//										{
	//											if (checkCyclicPair4digit(cyclicSet.at(4), cyclicSet.at(5)))
	//											{
	//												if (checkCyclicPair4digit(cyclicSet.at(5), cyclicSet.at(0)))
	//												{
	//													setisFound = true;
	//													break;
	//												}
	//											}
	//										}
	//									}
	//								}
	//							}
	//						} while (std::next_permutation(cyclicSet.begin(), cyclicSet.end()));

	//						if (setisFound)
	//						{
	//							break;
	//						}
	//					}

	//					if (setisFound)
	//					{
	//						break;
	//					}
	//				}

	//				if (setisFound)
	//				{
	//					break;
	//				}
	//			}

	//			if (setisFound)
	//			{
	//				break;
	//			}
	//		}

	//		if (setisFound)
	//		{
	//			break;
	//		}
	//	}

	//	if (setisFound)
	//	{
	//		break;
	//	}
	//}