#!/bin/bash

# k-values test
echo "doing k_values test"
dir="./graphs/rand_graphs"
for k_value in {2,4,8,16}; do 
    outfile_name="results/k-results/k_${k_value}.csv"

    echo "testing k value - ${k_value}:"
    echo "FILE_NAME,VERTEX_NUM,EDGES_NUM,INSERTS,UPDATES,DELETES,R_AVG,DURATION,RESIDENT_MEM" > "$outfile_name"
    
    while IFS= read -r graph_file; do
        echo "   test for ${graph_file}"
        
        # exec dijk and sets temporary file to get mem usage.
        /usr/bin/time -v ./build/dijk "?" "?" "$k_value" "$graph_file" "$outfile_name" < "$graph_file" 2> tmp_time.txt
        
        # get mem usage in kb
        mem_usage=$(grep "Maximum resident set size" tmp_time.txt | awk '{print $6}')
        
        # rmv temporary file
        rm -f tmp_time.txt
        
        # concat memory usage to csv record
        sed -i '$ s/$/,'"${mem_usage}"'/' "$outfile_name"
        
    done < <(find "$dir" -type f)
done

# rand edges test
echo "testing var in edges"
dir="./graphs/change_edges"
outfile_name="results/var_edges.csv"
echo "FILE_NAME,VERTEX_NUM,EDGES_NUM,INSERTS,UPDATES,DELETES,R_AVG,DURATION,RESIDENT_MEM" > "$outfile_name"

while IFS= read -r graph_file; do
    echo "   test for ${graph_file}"
    
    # exec dijk and sets temporary file to get mem usage.
    /usr/bin/time -v ./build/dijk "?" "?" "2" "$graph_file" "$outfile_name" < "$graph_file" 2> tmp_time.txt
    
    # get mem usage in kb
    mem_usage=$(grep "Maximum resident set size" tmp_time.txt | awk '{print $6}')
    
    # rmv temporary file
    rm -f tmp_time.txt
    
    # concat memory usage to csv record
    sed -i '$ s/$/,'"${mem_usage}"'/' "$outfile_name"
    
done < <(find "$dir" -type f)

# rand vertex test
echo "testing var in edges"
dir="./graphs/change_vertices"
outfile_name="results/var_vertex.csv"
echo "FILE_NAME,VERTEX_NUM,EDGES_NUM,INSERTS,UPDATES,DELETES,R_AVG,DURATION,RESIDENT_MEM" > "$outfile_name"

while IFS= read -r graph_file; do
    echo "   test for ${graph_file}"
    
    # exec dijk and sets temporary file to get mem usage.
    /usr/bin/time -v ./build/dijk "?" "?" "2" "$graph_file" "$outfile_name" < "$graph_file" 2> tmp_time.txt
    
    # get mem usage in kb
    mem_usage=$(grep "Maximum resident set size" tmp_time.txt | awk '{print $6}')
    
    # rmv temporary file
    rm -f tmp_time.txt
    
    # concat memory usage to csv record
    sed -i '$ s/$/,'"${mem_usage}"'/' "$outfile_name"
    
done < <(find "$dir" -type f)


# dijkstra test
echo "testing dijkstra"
graph_file="./graphs/dimacs_graphs/USA-road-d.NY.gr"
outfile_name="results/NY_stats.csv"
echo "FILE_NAME,VERTEX_NUM,EDGES_NUM,INSERTS,UPDATES,DELETES,R_AVG,DURATION,RESIDENT_MEM" > "$outfile_name"

for i in {1..30}; do 
    echo "   test for ${i}"
    # exec dijk and sets temporary file to get mem usage.
    /usr/bin/time -v ./build/dijk "?" "?" "2" "$graph_file" "$outfile_name" < "$graph_file" 2> tmp_time.txt
    
    # get mem usage in kb
    mem_usage=$(grep "Maximum resident set size" tmp_time.txt | awk '{print $6}')
    
    # rmv temporary file
    rm -f tmp_time.txt
    
    # concat memory usage to csv record
    sed -i '$ s/$/,'"${mem_usage}"'/' "$outfile_name"
done 
