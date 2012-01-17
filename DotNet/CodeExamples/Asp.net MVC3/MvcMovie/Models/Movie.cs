using System;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations;
using System.Collections.Generic;

using System.Data.Entity.Database;

namespace MvcMovie.Models {

    public class Movie {
        public int ID { get; set; }

        [Required(ErrorMessage="Title is required")]
        public string Title { get; set; }

          [Required] public DateTime ReleaseDate { get; set; }
        public string Genre { get; set; }

        [Required]
        [Range(1, 100, ErrorMessage = "Price must be between $1 and $100")]
        public decimal Price { get; set; }

        [StringLength(5)]
        public string Rating { get; set; }

        // Uncomment Rating2 to for DB drop
        //public string Rating2 { get; set; }

    }

    public class MovieDBContext : DbContext {
        public DbSet<Movie> Movies { get; set; }

        protected override void OnModelCreating(
            System.Data.Entity.ModelConfiguration.ModelBuilder modelBuilder) {
            modelBuilder.Entity<Movie>().Property(p => p.Price).HasPrecision(18, 2);
        }

    }

 public class MovieInitializer : DropCreateDatabaseIfModelChanges<MovieDBContext> {
     protected override void Seed(MovieDBContext context) {
         var movies = new List<Movie>
     {
         new Movie { Title = "When Harry Met Sally", 
                     ReleaseDate=DateTime.Parse("1989-1-11"), 
                     Genre="Romantic Comedy",
                     Rating="R",
                     Price=9.99M},

          new Movie { Title = "Ghostbusters 2", 
                     ReleaseDate=DateTime.Parse("1986-2-23"), 
                     Genre="Comedy",
                     Rating="R",
                     Price=7.99M}, 
                     
     };

         movies.ForEach(d => context.Movies.Add(d));
     }
 }

}