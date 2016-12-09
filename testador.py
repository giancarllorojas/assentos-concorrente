#!/usr/bin/python3
# -*- coding: utf-8 -*-
import sys
from collections import namedtuple
Valores = namedtuple('Valores', ['op', 'id', 'pos', 'mapa'])
erros = []

if(len(sys.argv) < 2):
    print("execute: testador.py <log a ser testado>")

def compara_mapa(mapa_comparar):
	#print('buffer:')
	#print(mapa)
	#print('esperado:')
	#print(mapa_comparar)
	#print('resultado:')
	#print(mapa_comparar)
	for i in range(0, len(mapa_comparar)):
		#print(mapa[i])
		if(int(mapa[i]) != int(mapa_comparar[i])):
			#print(False)
			return False
	#print(True)
	return True

def op1(vals):
	#print('op1: id ' + str(id))
	#compara os mapas
	if not (compara_mapa(vals.mapa)):
		e = "Erro na operacao: 1," + str(vals.id) + ",[" + ', '.join(str(e) for e in vals.mapa) + ']\n'
		e = e + 'mapa:' + '[' + ', '.join(str(e) for e in mapa) + ']' + '\n' + 'mapa_c:' + '[' + ', '.join(str(e) for e in vals.mapa) + ']'
		erros.append(e)
        
def op2(vals):
	#Verifica se ‚ None, pois em casos que nao tem assentos disponiveis, 
	#entao a opera‡ao 2 nao vai achar um assento para alocar, ficando None
	if(vals.pos != None):
		#caso ache um vazio, aloque para o id
		if(mapa[vals.pos] == 0):
			mapa[vals.pos] = vals.id
	#compara os mapas
	#print(mapa)
	if not (compara_mapa(vals.mapa)):
		e = "Erro na operacao: 2," + str(vals.id) + "," + str(vals.pos) + ",[" + ', '.join(str(e) for e in vals.mapa) + ']\n'
		e = e + 'mapa:' + '[' + ', '.join(str(e) for e in mapa) + ']' + '\n' + 'mapa_c:' + '[' + ', '.join(str(e) for e in vals.mapa) + ']'
		erros.append(e)
	return mapa

def op3(vals):
	#print('op3: id ' + str(id)+ ' pos_assento ' + str(pos_assento))
	#aloca um assento no mapa do buffer caso o assento esteja vazio
	#print(vals.mapa)
	if(mapa[vals.pos] == 0):
		mapa[vals.pos] = vals.id
	#print(vals.mapa)
	#compara os mapas
	if not (compara_mapa(vals.mapa)):
		e = "Erro na operacao: 3," + str(vals.id) + "," + str(vals.pos) + ",[" + ', '.join(str(e) for e in vals.mapa) + ']\n'
		e = e +  'mapa:' + '[' + ', '.join(str(e) for e in mapa) + ']' + '\n' + 'mapa_c:' + '[' + ', '.join(str(e) for e in vals.mapa) + ']'
		erros.append(e)
	return mapa

def op4(vals):
	#print('op4: id ' + str(id)+ ' pos_assento ' + str(pos_assento))
	#libera um assento no mapa do buffer
	if(mapa[vals.pos] != 0):
		mapa[vals.pos] = 0
	
	#compara os mapas
	if not (compara_mapa(vals.mapa)):
		e = "Erro na operacao: 4," + str(vals.id) + "," + str(vals.pos) + ",[" + ', '.join(str(e) for e in vals.mapa) + ']\n'
		e = e + 'mapa:' + '[' + ', '.join(str(e) for e in mapa) + ']' + '\n' + 'mapa_c:' + '[' + ', '.join(str(e) for e in vals.mapa) + ']'

		erros.append(e)
	return mapa

'''
Funcao que processa as linhas do log, pegando os valores da string 
Valores: operacao, id do usuario, posicao do assento e mapa de assentos
'''
def processa_linha(linha):
	i = 0
	ch = ''
	while(True):
		if(linha[i] == '['):
			break
		i += 1
	#print(i)
	valores = linha[0:i-1].split(',')
	mapa = [ int(x) for x in linha[i+1:-2].split(',') ]
	#print(valores)
	#print(mapa)
	operacao = int(valores[0])
	id_usuario = int(valores[1])
	if(len(valores) == 3):
		pos_assento = int(valores[2])
	else:
		pos_assento = None
	return Valores(operacao, id_usuario, pos_assento, mapa)

'''
Abre o arquivo, pega a quantidade de assentos para inicializar um mapa de assentos no buffer, entao 
percorre linha por linha no arquivo, chamando a funcao processa_linha(linha) e pegando os valores para
entao chamar as funcoes que verificam cada uma das operacoes(op1, op2, op3 e op4)
'''
with open(sys.argv[1], "r") as arq:
	conteudo = arq.readlines()
	qtd_assentos = int(conteudo.pop(0))
	mapa = [0] * qtd_assentos
	for linha in conteudo:
		vals = processa_linha(linha)
		#print('####################')
		#print(vals)
		#print(mapa)
		if(vals.op == 1):
			op1(vals)
		elif(vals.op == 2):
			mapa = op2(vals)
		elif(vals.op == 3):
			mapa = op3(vals)
		elif(vals.op == 4):
			mapa = op4(vals)

if(len(erros)):
	for erro in erros:
		print(erro + '\n')
	print('Quantidade de erros:' + str(len(erros)))
		
else:
	print('################## O log passou nos testes #######################')